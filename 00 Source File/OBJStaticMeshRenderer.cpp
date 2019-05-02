/**
* @file OBJStaticMeshRenderer.cpp
* @brief OBJ形式のスタティックメッシュ描画クラス実装ファイル
* @author Ryunosuke Honda.
*/
#include "OBJStaticMeshRenderer.h"

#include "ShaderConstantBuffer.h"
#include "ColorConstantBuffer.h"

#include "Camera.h"
#include "DirectionalLightDesc.h"

OBJStaticMeshRenderer::OBJStaticMeshRenderer() :
	base(),
	mpVertexShader(),
	mpVertexLayout(),
	mpPixelShader(),
	mpConstantBuffer0(),
	mpConstantBuffer1()
{
}

OBJStaticMeshRenderer::~OBJStaticMeshRenderer()
{
	SAFE_RELEASE(mpConstantBuffer0);
	SAFE_RELEASE(mpConstantBuffer1);
	SAFE_RELEASE(mpVertexLayout);
	SAFE_RELEASE(mpVertexShader);
	SAFE_RELEASE(mpPixelShader);
}

void OBJStaticMeshRenderer::addMesh(ID3D11Device * pDevice, const OBJMeshID & id, const LPSTR & fileName)
{
	add(id, new OBJStaticMesh(pDevice, fileName));
}

HRESULT OBJStaticMeshRenderer::init(ID3D11Device * pDevice)
{
	//hlslファイル読み込み ブロブ作成　ブロブとはシェーダーの塊みたいなもの。XXシェーダーとして特徴を持たない。後で各種シェーダーに成り得る。
	ID3DBlob *pCompiledShader = NULL;
	ID3DBlob *pErrors = NULL;
	//ブロブからバーテックスシェーダー作成
	SetShaderDirectory();
	if (FAILED(D3DX10CompileFromFile(L"OBJ_Material_Texture.hlsl", NULL, NULL, "VS", "vs_5_0", 0, 0, NULL, &pCompiledShader, &pErrors, NULL)))
	{
		MessageBox(0, L"hlsl読み込み失敗", NULL, MB_OK);
		return E_FAIL;
	}
	SAFE_RELEASE(pErrors);

	if (FAILED(pDevice->CreateVertexShader(pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), NULL, &mpVertexShader)))
	{
		SAFE_RELEASE(pCompiledShader);
		MessageBox(0, L"バーテックスシェーダー作成失敗", NULL, MB_OK);
		return E_FAIL;
	}
	//頂点インプットレイアウトを定義	
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = sizeof(layout) / sizeof(layout[0]);
	//頂点インプットレイアウトを作成
	if (FAILED(pDevice->CreateInputLayout(layout, numElements, pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), &mpVertexLayout)))
	{
		return FALSE;
	}
	//ブロブからピクセルシェーダー作成
	if (FAILED(D3DX11CompileFromFile(L"OBJ_Material_Texture.hlsl", NULL, NULL, "PS", "ps_5_0", 0, 0, NULL, &pCompiledShader, &pErrors, NULL)))
	{
		MessageBox(0, L"hlsl読み込み失敗", NULL, MB_OK);
		return E_FAIL;
	}
	SAFE_RELEASE(pErrors);
	if (FAILED(pDevice->CreatePixelShader(pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), NULL, &mpPixelShader)))
	{
		SAFE_RELEASE(pCompiledShader);
		MessageBox(0, L"ピクセルシェーダー作成失敗", NULL, MB_OK);
		return E_FAIL;
	}

	SAFE_RELEASE(pCompiledShader);

	//コンスタントバッファー作成(OBJStaticMeshクラス用）　変換行列渡し用
	D3D11_BUFFER_DESC cb;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.ByteWidth = sizeof(ShaderConstantBuffer);
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.Usage = D3D11_USAGE_DYNAMIC;

	if (FAILED(pDevice->CreateBuffer(&cb, NULL, &mpConstantBuffer0)))
	{
		return E_FAIL;
	}

	//コンスタントバッファー作成(OBJStaticMeshクラス用）  マテリアル渡し用
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.ByteWidth = sizeof(ColorConstantBuffer);
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.Usage = D3D11_USAGE_DYNAMIC;

	if (FAILED(pDevice->CreateBuffer(&cb, NULL, &mpConstantBuffer1)))
	{
		return E_FAIL;
	}

	return S_OK;
}

void OBJStaticMeshRenderer::render(ID3D11DeviceContext * pDeviceContext, const Camera * pCamera, const DirectionalLightDesc & light)
{
	//使用するシェーダーの登録
	pDeviceContext->VSSetShader(mpVertexShader, NULL, 0);
	pDeviceContext->PSSetShader(mpPixelShader, NULL, 0);
	pDeviceContext->GSSetShader(NULL, NULL, 0);

	//頂点インプットレイアウトをセット
	pDeviceContext->IASetInputLayout(mpVertexLayout);
	//プリミティブ・トポロジーをセット
	pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	int dataCount = mData.size();
	for (int i = 0; i < dataCount; i++)
	{
		const OBJStaticMeshRenderDesc* pDesc = mData[i];

		//カリングするレイヤーならスキップ
		if (pCamera->isCulling(pDesc->mpTransform->Layer)) continue;

		//ワールド行列の設定
		Matrix4x4 world;
		pDesc->mpTransform->makeWorld(&world);

		//シェーダーのコンスタントバッファーに各種データを渡す
		D3D11_MAPPED_SUBRESOURCE pData;
		if (SUCCEEDED(pDeviceContext->Map(mpConstantBuffer0, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
		{
			ShaderConstantBuffer cb;
			//ワールド行列を渡す
			cb.mW = world;
			D3DXMatrixTranspose(&cb.mW, &cb.mW);
			//ワールド、カメラ、射影行列を渡す
			Matrix4x4 m = world * pCamera->getView() *pCamera->getProj();
			cb.mWVP = m;
			D3DXMatrixTranspose(&cb.mWVP, &cb.mWVP);
			//ライトの方向を渡す
			cb.vLightDir = Vector4(light.direction, 0);
			//視点位置を渡す
			cb.vEye = Vector4(pCamera->getLookPt(), 0);

			memcpy_s(pData.pData, pData.RowPitch, (void*)&cb, sizeof(ShaderConstantBuffer));
			pDeviceContext->Unmap(mpConstantBuffer0, 0);
		}

		//このコンスタントバッファーを使うシェーダーの登録
		pDeviceContext->VSSetConstantBuffers(0, 1, &mpConstantBuffer0);
		pDeviceContext->PSSetConstantBuffers(0, 1, &mpConstantBuffer0);

		get(pDesc->mID)->render(pDeviceContext, mpConstantBuffer1, pDesc);
	}
}

void OBJStaticMeshRenderer::renderTransparent(ID3D11DeviceContext * pDeviceContext, const Camera * pCamera, const DirectionalLightDesc & light)
{
	//使用するシェーダーの登録
	pDeviceContext->VSSetShader(mpVertexShader, NULL, 0);
	pDeviceContext->PSSetShader(mpPixelShader, NULL, 0);
	pDeviceContext->GSSetShader(NULL, NULL, 0);

	//頂点インプットレイアウトをセット
	pDeviceContext->IASetInputLayout(mpVertexLayout);
	//プリミティブ・トポロジーをセット
	pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	int dataCount = mTransparentData.size();
	for (int i = 0; i < dataCount; i++)
	{
		const OBJStaticMeshRenderDesc* pDesc = mTransparentData[i];

		//カリングするレイヤーならスキップ
		if (pCamera->isCulling(pDesc->mpTransform->Layer)) continue;

		//ワールド行列の設定
		Matrix4x4 world;
		pDesc->mpTransform->makeWorld(&world);

		//シェーダーのコンスタントバッファーに各種データを渡す
		D3D11_MAPPED_SUBRESOURCE pData;
		if (SUCCEEDED(pDeviceContext->Map(mpConstantBuffer0, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
		{
			ShaderConstantBuffer cb;
			//ワールド行列を渡す
			cb.mW = world;
			D3DXMatrixTranspose(&cb.mW, &cb.mW);
			//ワールド、カメラ、射影行列を渡す
			Matrix4x4 m = world * pCamera->getView() *pCamera->getProj();
			cb.mWVP = m;
			D3DXMatrixTranspose(&cb.mWVP, &cb.mWVP);
			//ライトの方向を渡す
			cb.vLightDir = Vector4(light.direction, 0);
			//視点位置を渡す
			cb.vEye = Vector4(pCamera->getLookPt(), 0);

			memcpy_s(pData.pData, pData.RowPitch, (void*)&cb, sizeof(ShaderConstantBuffer));
			pDeviceContext->Unmap(mpConstantBuffer0, 0);
		}

		//このコンスタントバッファーを使うシェーダーの登録
		pDeviceContext->VSSetConstantBuffers(0, 1, &mpConstantBuffer0);
		pDeviceContext->PSSetConstantBuffers(0, 1, &mpConstantBuffer0);

		get(pDesc->mID)->render(pDeviceContext, mpConstantBuffer1, pDesc);
	}
}

/* End of File *****************************************************/