/**
* @file SpriteRenderer.cpp
* @brief スプライト管理クラス実装ファイル
* @author Ryunosuke Honda.
*/
#include "SpriteRenderer.h"

#include <D3DX11.h>
#include "SpriteConstantBuffer.h"
#include "SpriteRenderDesc.h"
#include "MyVertex.h"
#include "Camera.h"
#include "DirectionalLightDesc.h"
#include "UIImageRenderDesc.h"

SpriteRenderer::SpriteRenderer()
{
}

SpriteRenderer::~SpriteRenderer()
{
	SAFE_RELEASE(mpVertexLayout);
	SAFE_RELEASE(mpConstantBuffer);
	SAFE_RELEASE(mpPixelShader);
	SAFE_RELEASE(mpVertexShader);
}

HRESULT SpriteRenderer::init(ID3D11Device * pDevice)
{
	SetShaderDirectory();
	//hlslファイル読み込み ブロブ作成　ブロブとはシェーダーの塊みたいなもの。XXシェーダーとして特徴を持たない。後で各種シェーダーに成り得る。
	ID3D10Blob *pCompiledShader = NULL;
	ID3D10Blob *pErrors = NULL;
	//ブロブからバーテックスシェーダー作成
	if (FAILED(D3DX11CompileFromFile(L"Sprite_Material_Texture.hlsl", NULL, NULL, "VS", "vs_5_0", 0, 0, NULL, &pCompiledShader, &pErrors, NULL)))
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
	if (FAILED(D3DX11CompileFromFile(L"Sprite_Material_Texture.hlsl", NULL, NULL, "PS", "ps_5_0", 0, 0, NULL, &pCompiledShader, &pErrors, NULL)))
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

	//コンスタントバッファー作成
	D3D11_BUFFER_DESC cb;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.ByteWidth = sizeof(SpriteConstantBuffer);
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.Usage = D3D11_USAGE_DYNAMIC;

	if (FAILED(pDevice->CreateBuffer(&cb, NULL, &mpConstantBuffer)))
	{
		return E_FAIL;
	}
	return S_OK;
}

void SpriteRenderer::addSprite(ID3D11Device * pDevice, const TextureID & id, const LPCWSTR & fileName)
{
	add(id, new Sprite(pDevice, fileName));
}

void SpriteRenderer::registerUIData(const UIImageRenderDesc * pDesc)
{
	//簡易のため記述子のディフューズ色のアルファ値で判別
	if (pDesc->mDiffuse.a > 0.999f)
	{
		mUIData.push_back(pDesc);
	}
	else
	{
		mTransparentUIData.push_back(pDesc);
	}
}

void SpriteRenderer::renderUI(ID3D11DeviceContext * pDeviceContext, const Matrix4x4& UIMatrix)
{
	//描画設定を適用
	initRenderConfig(pDeviceContext);

	//全データの描画
	for (int i = 0; i < mUIData.size(); i++)
	{
		renderUIImage(mUIData[i], pDeviceContext, UIMatrix);
	}
}

void SpriteRenderer::renderTransparentUI(ID3D11DeviceContext * pDeviceContext, const Matrix4x4 & UIMatrix)
{
	//描画設定を適用
	initRenderConfig(pDeviceContext);

	//全データの描画
	for (int i = 0; i < mTransparentUIData.size(); i++)
	{
		renderUIImage(mTransparentUIData[i], pDeviceContext, UIMatrix);
	}
}

void SpriteRenderer::clearUI()
{
	mUIData.clear();
	mTransparentUIData.clear();
}

void SpriteRenderer::render(ID3D11DeviceContext * pDeviceContext, const Camera * pCamera, const DirectionalLightDesc& light)
{
	//描画設定を適用
	initRenderConfig(pDeviceContext);

	//全データの描画
	for (int i = 0; i < mData.size(); i++)
	{
		renderSprite(mData[i], pDeviceContext, pCamera, light);
	}
}

void SpriteRenderer::renderTransparent(ID3D11DeviceContext * pDeviceContext, const Camera * pCamera, const DirectionalLightDesc & light)
{
	//描画設定を適用
	initRenderConfig(pDeviceContext);

	//全データの描画
	for (int i = 0; i < mTransparentData.size(); i++)
	{
		renderSprite(mTransparentData[i], pDeviceContext, pCamera, light);
	}
}

void SpriteRenderer::initRenderConfig(ID3D11DeviceContext * pDeviceContext)
{
	//使用するシェーダーの登録	
	pDeviceContext->VSSetShader(mpVertexShader, NULL, 0);
	pDeviceContext->PSSetShader(mpPixelShader, NULL, 0);

	//頂点インプットレイアウトをセット
	pDeviceContext->IASetInputLayout(mpVertexLayout);

	//プリミティブ・トポロジーをセット
	pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
}

void SpriteRenderer::renderSprite(const SpriteRenderDesc * pDesc, ID3D11DeviceContext * pDeviceContext, const Camera * pCamera, const DirectionalLightDesc & light)
{
	//カリングするレイヤーならスキップ
	if (pCamera->isCulling(pDesc->mpTransform->Layer)) return;

	//シェーダーのコンスタントバッファーに各種データを渡す	
	D3D11_MAPPED_SUBRESOURCE pData;
	if (SUCCEEDED(pDeviceContext->Map(mpConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
	{
		SpriteConstantBuffer cb;
		//ワールド行列の設定
		Matrix4x4 world;
		pDesc->mpTransform->makeWorld(&world);
		//ワールド行列を渡す
		cb.mW = world;
		D3DXMatrixTranspose(&cb.mW, &cb.mW);
		//ワールド、カメラ、射影行列を渡す
		Matrix4x4 m = world * pCamera->getView() * pCamera->getProj();
		cb.mWVP = m;
		D3DXMatrixTranspose(&cb.mWVP, &cb.mWVP);
		//カラーを渡す 
		cb.mColor = pDesc->mDiffuse;
		//ライト方向を渡す
		cb.vLightDir = Vector4(light.direction, 0);
		//カメラの位置(視点)をシェーダーに渡す
		cb.vEye = Vector4(pCamera->getLookPt(), 0.0f);

		memcpy_s(pData.pData, pData.RowPitch, (void*)&cb, sizeof(SpriteConstantBuffer));
		pDeviceContext->Unmap(mpConstantBuffer, 0);
	}

	//このコンスタントバッファーを使うシェーダーの登録
	pDeviceContext->VSSetConstantBuffers(0, 1, &mpConstantBuffer);
	pDeviceContext->PSSetConstantBuffers(0, 1, &mpConstantBuffer);

	//設定したあとはスプライトクラスに任せる
	get(pDesc->mID)->render(pDeviceContext);
}

void SpriteRenderer::renderUIImage(const UIImageRenderDesc * pDesc, ID3D11DeviceContext * pDeviceContext, const Matrix4x4 & UIMatrix)
{
	//ワールド変換
	Matrix4x4 world;
	pDesc->mpRect->makeWorld(&world);

	//シェーダーのコンスタントバッファーに各種データを渡す	
	D3D11_MAPPED_SUBRESOURCE pData;
	if (SUCCEEDED(pDeviceContext->Map(mpConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
	{
		SpriteConstantBuffer cb;
		//ワールド行列を渡す
		cb.mW = world;
		D3DXMatrixTranspose(&cb.mW, &cb.mW);
		//ワールド座標をUI座標系に変換して渡す
		Matrix4x4 m = world * UIMatrix;
		cb.mWVP = m;
		D3DXMatrixTranspose(&cb.mWVP, &cb.mWVP);
		//カラーを渡す 
		cb.mColor = pDesc->mDiffuse;
		//ライト方向を渡す
		cb.vLightDir = Vector4(1, 1, 1, 1);
		//カメラの位置(視点)をシェーダーに渡す
		cb.vEye = Vector4(0, 0, -10, 0);

		memcpy_s(pData.pData, pData.RowPitch, (void*)&cb, sizeof(SpriteConstantBuffer));
		pDeviceContext->Unmap(mpConstantBuffer, 0);
	}
	//このコンスタントバッファーを使うシェーダーの登録
	pDeviceContext->VSSetConstantBuffers(0, 1, &mpConstantBuffer);
	pDeviceContext->PSSetConstantBuffers(0, 1, &mpConstantBuffer);

	//設定したあとはスプライトクラスに任せる
	get(pDesc->mID)->render(pDeviceContext);
}

/* End of File *****************************************************/