/**
* @file FBXSkinMeshRenderer.cpp
* @brief FBXスキンメッシュ管理クラス実装ファイル
* @author Ryunosuke Honda.
*/
#include "FBXSkinMeshRenderer.h"
#include <d3dx11.h>

#include "SkinShaderBone.h"
#include "ColorConstantBuffer.h"
#include "ShaderLightEyevec.h"
#include "ShaderWorldColor.h"
#include "Camera.h"
#include "DirectionalLightDesc.h"

FBXSkinMeshRenderer::FBXSkinMeshRenderer() :
	base(),
	mpVertexShader(),
	mpVertexLayout(),
	mpPixelShader(),
	mpConstantBuffer0(),
	mpConstantBuffer1(),
	mpConstantBuffer2()
{
}

FBXSkinMeshRenderer::~FBXSkinMeshRenderer()
{
	SAFE_RELEASE(mpConstantBuffer0);
	SAFE_RELEASE(mpConstantBuffer1);
	SAFE_RELEASE(mpConstantBuffer2);
	SAFE_RELEASE(mpVertexLayout);
	SAFE_RELEASE(mpVertexShader);
	SAFE_RELEASE(mpPixelShader);
}

HRESULT FBXSkinMeshRenderer::init(ID3D11Device * pDevice)
{
	//ブロブからバーテックスシェーダー作成
	ID3DBlob *pCompiledShader = NULL;
	ID3DBlob *pErrors = NULL;
	SetShaderDirectory();
	if (FAILED(D3DX11CompileFromFile(L"FBXSkin_Material_Texture.hlsl", NULL, NULL, "VSSkin", "vs_5_0", 0, 0, NULL, &pCompiledShader, &pErrors, NULL)))
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
	D3D11_INPUT_ELEMENT_DESC layout_Skin[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "BONE_INDEX", 0, DXGI_FORMAT_R32G32B32A32_UINT, 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "BONE_WEIGHT", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 48, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = sizeof(layout_Skin) / sizeof(layout_Skin[0]);
	//頂点インプットレイアウトを作成
	if (FAILED(pDevice->CreateInputLayout(layout_Skin, numElements, pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), &mpVertexLayout)))
	{
		return FALSE;
	}
	//ブロブからピクセルシェーダー作成
	if (FAILED(D3DX11CompileFromFile(L"FBXSkin_Material_Texture.hlsl", NULL, NULL, "PSSkin", "ps_5_0", 0, 0, NULL, &pCompiledShader, &pErrors, NULL)))
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

	//コンスタントバッファー作成  (FBXSkinMeshクラス用）ライト、視点渡し用
	D3D11_BUFFER_DESC cb;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.ByteWidth = sizeof(ShaderLightEyevec);
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;
	cb.Usage = D3D11_USAGE_DYNAMIC;
	if (FAILED(pDevice->CreateBuffer(&cb, NULL, &mpConstantBuffer0)))
	{
		MessageBox(0, L"コンスタントバッファー0作成失敗", NULL, MB_OK);
		return E_FAIL;
	}

	//コンスタントバッファー作成  (FBXSkinMeshクラス用）変換行列、マテリアル渡し用
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.ByteWidth = sizeof(ShaderWorldColor);
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;
	cb.Usage = D3D11_USAGE_DYNAMIC;
	if (FAILED(pDevice->CreateBuffer(&cb, NULL, &mpConstantBuffer1)))
	{
		MessageBox(0, L"コンスタントバッファー1作成失敗", NULL, MB_OK);
		return E_FAIL;
	}

	//コンスタントバッファー作成   (FBXSkinMeshクラス用）ボーン用
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.ByteWidth = sizeof(SkinShaderBone);
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;
	cb.Usage = D3D11_USAGE_DYNAMIC;
	if (FAILED(pDevice->CreateBuffer(&cb, NULL, &mpConstantBuffer2)))
	{
		return E_FAIL;
	}

	return S_OK;
}

void FBXSkinMeshRenderer::addMesh(ID3D11Device * pDevice, const FBXSkinID & id, const LPSTR & fileName)
{
	//登録されていなければ新規に登録
	add(id, new FBXSkinMesh(pDevice, fileName));
}

void FBXSkinMeshRenderer::render(ID3D11DeviceContext* pDeviceContext, const Camera* pCamera, const DirectionalLightDesc & light)
{
	////使用するシェーダーの登録	
	pDeviceContext->VSSetShader(mpVertexShader, NULL, 0);
	pDeviceContext->PSSetShader(mpPixelShader, NULL, 0);

	//頂点インプットレイアウトをセット
	pDeviceContext->IASetInputLayout(mpVertexLayout);

	int dataCount = mData.size();
	for (int i = 0; i < dataCount; i++)
	{
		const FBXSkinMeshRenderDesc* pDesc = mData[i];

		//カリングするレイヤーならスキップ
		if (pCamera->isCulling(pDesc->mpTransform->Layer)) continue;

		//シェーダーのコンスタントバッファーに各種データを渡す	
		D3D11_MAPPED_SUBRESOURCE pData;
		if (SUCCEEDED(pDeviceContext->Map(mpConstantBuffer0, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
		{
			ShaderLightEyevec cb;
			//ライトの方向を渡す
			cb.vLightDir = Vector4(light.direction, 0);
			//視点位置を渡す
			cb.vEye = Vector4(pCamera->getLookPt(), 0);

			memcpy_s(pData.pData, pData.RowPitch, (void*)&cb, sizeof(ShaderLightEyevec));
			pDeviceContext->Unmap(mpConstantBuffer0, 0);
		}
		pDeviceContext->VSSetConstantBuffers(0, 1, &mpConstantBuffer0);
		//アニメーションフレームを進める　スキンを更新
		FBXSkinMesh* mesh = get(pDesc->mID).get();
		mesh->setNewPoseMatrices(pDesc->mFrame);
		pDeviceContext->PSSetConstantBuffers(0, 1, &mpConstantBuffer0);

		//フレームを進めたことにより変化したポーズ（ボーンの行列）をシェーダーに渡す
		if (SUCCEEDED(pDeviceContext->Map(mpConstantBuffer2, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
		{
			SkinShaderBone sg;
			for (int i = 0; i < mesh->getBoneCount(); i++)
			{
				Matrix4x4 mat = mesh->getCurrentPoseMatrix(i);
				D3DXMatrixTranspose(&mat, &mat);
				sg.mBone[i] = mat;
			}
			memcpy_s(pData.pData, pData.RowPitch, (void*)&sg, sizeof(SkinShaderBone));
			pDeviceContext->Unmap(mpConstantBuffer2, 0);
		}
		pDeviceContext->VSSetConstantBuffers(2, 1, &mpConstantBuffer2);
		pDeviceContext->PSSetConstantBuffers(2, 1, &mpConstantBuffer2);

		get(pDesc->mID)->render(pDeviceContext, mpConstantBuffer1, pCamera, pDesc);
	}
}

void FBXSkinMeshRenderer::renderTransparent(ID3D11DeviceContext * pDeviceContext, const Camera * pCamera, const DirectionalLightDesc & light)
{
	////使用するシェーダーの登録	
	pDeviceContext->VSSetShader(mpVertexShader, NULL, 0);
	pDeviceContext->PSSetShader(mpPixelShader, NULL, 0);

	//頂点インプットレイアウトをセット
	pDeviceContext->IASetInputLayout(mpVertexLayout);

	int dataCount = mTransparentData.size();
	for (int i = 0; i < dataCount; i++)
	{
		const FBXSkinMeshRenderDesc* pDesc = mTransparentData[i];

		//カリングするレイヤーならスキップ
		if (pCamera->isCulling(pDesc->mpTransform->Layer)) continue;

		//シェーダーのコンスタントバッファーに各種データを渡す	
		D3D11_MAPPED_SUBRESOURCE pData;
		if (SUCCEEDED(pDeviceContext->Map(mpConstantBuffer0, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
		{
			ShaderLightEyevec cb;
			//ライトの方向を渡す
			cb.vLightDir = Vector4(light.direction, 0);
			//視点位置を渡す
			cb.vEye = Vector4(pCamera->getLookPt(), 0);

			memcpy_s(pData.pData, pData.RowPitch, (void*)&cb, sizeof(ShaderLightEyevec));
			pDeviceContext->Unmap(mpConstantBuffer0, 0);
		}
		pDeviceContext->VSSetConstantBuffers(0, 1, &mpConstantBuffer0);
		//アニメーションフレームを進める　スキンを更新
		FBXSkinMesh* mesh = get(pDesc->mID).get();
		mesh->setNewPoseMatrices(pDesc->mFrame);
		pDeviceContext->PSSetConstantBuffers(0, 1, &mpConstantBuffer0);

		//フレームを進めたことにより変化したポーズ（ボーンの行列）をシェーダーに渡す
		if (SUCCEEDED(pDeviceContext->Map(mpConstantBuffer2, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
		{
			SkinShaderBone sg;
			for (int i = 0; i < mesh->getBoneCount(); i++)
			{
				Matrix4x4 mat = mesh->getCurrentPoseMatrix(i);
				D3DXMatrixTranspose(&mat, &mat);
				sg.mBone[i] = mat;
			}
			memcpy_s(pData.pData, pData.RowPitch, (void*)&sg, sizeof(SkinShaderBone));
			pDeviceContext->Unmap(mpConstantBuffer2, 0);
		}
		pDeviceContext->VSSetConstantBuffers(2, 1, &mpConstantBuffer2);
		pDeviceContext->PSSetConstantBuffers(2, 1, &mpConstantBuffer2);

		get(pDesc->mID)->render(pDeviceContext, mpConstantBuffer1, pCamera, pDesc);
	}
}

/* End of File *****************************************************/