/**
* @file FBXHierarchyMeshRenderer.cpp
* @brief FBX階層メッシュ描画クラス実装ファイル
* @author Ryunosuke Honda.
*/
#include "FBXHierarchyMeshRenderer.h"
#include "ShaderLightEyevec.h"
#include "ShaderWorldColor.h"
#include "Camera.h"
#include <d3dx11.h>

FBXHierarchyMeshRenderer::FBXHierarchyMeshRenderer():
	base(),
	mpVertexShader(),
	mpVertexLayout(),
	mpPixelShader(),
	mpConstantBuffer0(),
	mpConstantBuffer1(),
	mpConstantBuffer2()
{
}

FBXHierarchyMeshRenderer::~FBXHierarchyMeshRenderer()
{
}

HRESULT FBXHierarchyMeshRenderer::init(ID3D11Device * pDevice)
{
	//hlslファイル読み込み ブロブ作成　ブロブとはシェーダーの塊みたいなもの。XXシェーダーとして特徴を持たない。後で各種シェーダーに成り得る。
	ID3DBlob *pCompiledShader = NULL;
	ID3DBlob *pErrors = NULL;
	//ブロブからバーテックスシェーダー作成
	if (FAILED(D3DX11CompileFromFile(L"FBXHierarchy_Material_Texture.hlsl", NULL, NULL, "VS", "vs_5_0", 0, 0, NULL, &pCompiledShader, &pErrors, NULL)))
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
	if (FAILED(D3DX11CompileFromFile(L"FBXHierarchy_Material_Texture.hlsl", NULL, NULL, "PS", "ps_5_0", 0, 0, NULL, &pCompiledShader, &pErrors, NULL)))
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
	//コンスタントバッファー0作成 ライトと視点　渡し用
	D3D11_BUFFER_DESC cb;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.ByteWidth = sizeof(ShaderLightEyevec);
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;
	cb.Usage = D3D11_USAGE_DYNAMIC;

	if (FAILED(pDevice->CreateBuffer(&cb, NULL, &mpConstantBuffer0)))
	{
		return E_FAIL;
	}
	//コンスタントバッファー1作成  FBXMesh内で使用 変換行列とマテリアル用
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.ByteWidth = sizeof(ShaderWorldColor);
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;
	cb.Usage = D3D11_USAGE_DYNAMIC;

	if (FAILED(pDevice->CreateBuffer(&cb, NULL, &mpConstantBuffer1)))
	{
		return E_FAIL;
	}
	return S_OK;
}

void FBXHierarchyMeshRenderer::addMesh(ID3D11Device * pDevice, const FBXHierarchyID & id, const LPSTR & fileName)
{
	add(id, new FBXHierarchyMesh(pDevice, fileName));
}

void FBXHierarchyMeshRenderer::render(ID3D11DeviceContext * pDeviceContext, const Camera* pCamera, const DirectionalLightDesc& light)
{
	////使用するシェーダーの登録	
	pDeviceContext->VSSetShader(mpVertexShader, NULL, 0);
	pDeviceContext->PSSetShader(mpPixelShader, NULL, 0);
	//頂点インプットレイアウトをセット
	pDeviceContext->IASetInputLayout(mpVertexLayout);

	int dataCount = mData.size();
	for (int i = 0; i < dataCount; i++)
	{
		const FBXHierarchyMeshRenderDesc* pDesc = mData[i];

		//カリングするレイヤーならスキップ
		if (pCamera->isCulling(pDesc->mpTransform->Layer)) continue;

		//シェーダーのコンスタントバッファーに各種データを渡す	
		D3D11_MAPPED_SUBRESOURCE pData;
		if (SUCCEEDED(pDeviceContext->Map(mpConstantBuffer0, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
		{
			ShaderLightEyevec cb;
			//ライトの方向を渡す
			D3DXVECTOR3 vLightDir(0, 0, -1);
			D3DXVec3Normalize(&vLightDir, &vLightDir);
			cb.vLightDir = D3DXVECTOR4(vLightDir.x, vLightDir.y, vLightDir.z, 0.0f);
			//視点位置を渡す
			cb.vEye = Vector4(pCamera->getLookPt(), 0);

			memcpy_s(pData.pData, pData.RowPitch, (void*)&cb, sizeof(ShaderLightEyevec));
			pDeviceContext->Unmap(mpConstantBuffer0, 0);
		}
		pDeviceContext->VSSetConstantBuffers(0, 1, &mpConstantBuffer0);
		pDeviceContext->PSSetConstantBuffers(0, 1, &mpConstantBuffer0);

		//メッシュをレンダリング
		get(pDesc->mID)->render(pDeviceContext, mpConstantBuffer1, pCamera, pDesc);
	}
}

void FBXHierarchyMeshRenderer::renderTransparent(ID3D11DeviceContext * pDeviceContext, const Camera * pCamera, const DirectionalLightDesc & light)
{
	////使用するシェーダーの登録	
	pDeviceContext->VSSetShader(mpVertexShader, NULL, 0);
	pDeviceContext->PSSetShader(mpPixelShader, NULL, 0);
	//頂点インプットレイアウトをセット
	pDeviceContext->IASetInputLayout(mpVertexLayout);

	int dataCount = mTransparentData.size();
	for (int i = 0; i < dataCount; i++)
	{
		const FBXHierarchyMeshRenderDesc* pDesc = mTransparentData[i];

		//カリングするレイヤーならスキップ
		if (pCamera->isCulling(pDesc->mpTransform->Layer)) continue;

		//シェーダーのコンスタントバッファーに各種データを渡す	
		D3D11_MAPPED_SUBRESOURCE pData;
		if (SUCCEEDED(pDeviceContext->Map(mpConstantBuffer0, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
		{
			ShaderLightEyevec cb;
			//ライトの方向を渡す
			D3DXVECTOR3 vLightDir(0, 0, -1);
			D3DXVec3Normalize(&vLightDir, &vLightDir);
			cb.vLightDir = D3DXVECTOR4(vLightDir.x, vLightDir.y, vLightDir.z, 0.0f);
			//視点位置を渡す
			cb.vEye = Vector4(pCamera->getLookPt(), 0);

			memcpy_s(pData.pData, pData.RowPitch, (void*)&cb, sizeof(ShaderLightEyevec));
			pDeviceContext->Unmap(mpConstantBuffer0, 0);
		}
		pDeviceContext->VSSetConstantBuffers(0, 1, &mpConstantBuffer0);
		pDeviceContext->PSSetConstantBuffers(0, 1, &mpConstantBuffer0);

		//メッシュをレンダリング
		get(pDesc->mID)->render(pDeviceContext, mpConstantBuffer1, pCamera, pDesc);
	}
}

/* End of File *****************************************************/