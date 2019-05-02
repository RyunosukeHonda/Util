/**
* @file QuadRenderer.cpp
* @brief 四角形ポリゴン描画クラス実装ファイル
* @author Ryunosuke Honda.
*/
#include "QuadRenderer.h"

#include "QuadConstantBuffer.h"
#include <d3dx11.h>
#include "QuadRenderDesc.h"
#include "Camera.h"
#include "DirectionalLightDesc.h"
#include "UIQuadRenderDesc.h"

QuadRenderer::QuadRenderer()
{
}

QuadRenderer::~QuadRenderer()
{
}

void QuadRenderer::addQuad(ID3D11Device * pDevice, const ShaderTextureID & id, const LPCWSTR & fileName)
{
	add(id, new Quad(pDevice, fileName));
}

void QuadRenderer::registerUIData(const UIQuadRenderDesc *pDesc)
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

void QuadRenderer::renderUI(ID3D11DeviceContext * pDeviceContext, const Matrix4x4& UIMatrix)
{
	//描画設定を適用
	initRenderConfig(pDeviceContext);

	//全データの描画
	for (int i = 0; i < mUIData.size(); i++)
	{
		renderUIQuad(mUIData[i], pDeviceContext, UIMatrix);
	}
}

void QuadRenderer::renderTransparentUI(ID3D11DeviceContext * pDeviceContext, const Matrix4x4 & UIMatrix)
{
	//描画設定を適用
	initRenderConfig(pDeviceContext);

	//全データの描画
	for (int i = 0; i < mTransparentUIData.size(); i++)
	{
		renderUIQuad(mTransparentUIData[i], pDeviceContext, UIMatrix);
	}
}

void QuadRenderer::clearUI()
{
	mUIData.clear();
	mTransparentUIData.clear();
}

HRESULT QuadRenderer::init(ID3D11Device * pDevice)
{
	//コンスタントバッファー作成
	D3D11_BUFFER_DESC cb;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.ByteWidth = sizeof(QuadConstantBuffer);
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.Usage = D3D11_USAGE_DYNAMIC;

	if (FAILED(pDevice->CreateBuffer(&cb, NULL, &mpConstantBuffer)))
	{
		return E_FAIL;
	}
	return S_OK;
}

void QuadRenderer::render(ID3D11DeviceContext * pDeviceContext, const Camera * pCamera, const DirectionalLightDesc & light)
{
	//描画設定を適用
	initRenderConfig(pDeviceContext);

	//全データの描画
	for (int i = 0; i < mData.size(); i++)
	{
		renderQuad(mData[i], pDeviceContext, pCamera, light);
	}
}

void QuadRenderer::renderTransparent(ID3D11DeviceContext * pDeviceContext, const Camera * pCamera, const DirectionalLightDesc & light)
{
	//描画設定を適用
	initRenderConfig(pDeviceContext);

	//全データの描画
	for (int i = 0; i < mTransparentData.size(); i++)
	{
		renderQuad(mTransparentData[i], pDeviceContext, pCamera, light);
	}
}

void QuadRenderer::initRenderConfig(ID3D11DeviceContext * pDeviceContext)
{
	//プリミティブ・トポロジーをセット
	pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
}

void QuadRenderer::renderQuad(const QuadRenderDesc * pDesc, ID3D11DeviceContext * pDeviceContext, const Camera * pCamera, const DirectionalLightDesc & light)
{
	//カリングするレイヤーならスキップ
	if (pCamera->isCulling(pDesc->mpTransform->Layer)) return;

	//ワールド行列の設定
	Matrix4x4 world;
	pDesc->mpTransform->makeWorld(&world);

	//シェーダーのコンスタントバッファーに各種データを渡す	
	D3D11_MAPPED_SUBRESOURCE pData;
	if (SUCCEEDED(pDeviceContext->Map(mpConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
	{
		QuadConstantBuffer cb;
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
		//時間を渡す
		cb.mTime.x = pDesc->mTime;

		memcpy_s(pData.pData, pData.RowPitch, (void*)&cb, sizeof(QuadConstantBuffer));
		pDeviceContext->Unmap(mpConstantBuffer, 0);
	}
	//このコンスタントバッファーを使うシェーダーの登録
	pDeviceContext->VSSetConstantBuffers(0, 1, &mpConstantBuffer);
	pDeviceContext->PSSetConstantBuffers(0, 1, &mpConstantBuffer);

	//設定したあとはスプライトクラスに任せる
	get(pDesc->mID)->render(pDeviceContext);
}

void QuadRenderer::renderUIQuad(const UIQuadRenderDesc * pDesc, ID3D11DeviceContext * pDeviceContext, const Matrix4x4 & UIMatrix)
{
	//ワールド変換
	Matrix4x4 world;
	pDesc->mpRect->makeWorld(&world);

	//シェーダーのコンスタントバッファーに各種データを渡す	
	D3D11_MAPPED_SUBRESOURCE pData;
	if (SUCCEEDED(pDeviceContext->Map(mpConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
	{
		QuadConstantBuffer cb;
		//ワールド行列を渡す
		cb.mW = world;
		D3DXMatrixTranspose(&cb.mW, &cb.mW);
		//ワールド、カメラ、射影行列を渡す
		Matrix4x4 m = world * UIMatrix;
		cb.mWVP = m;
		D3DXMatrixTranspose(&cb.mWVP, &cb.mWVP);
		//カラーを渡す 
		cb.mColor = pDesc->mDiffuse;
		//ライト方向を渡す
		cb.vLightDir = Vector4(1, 1, 1, 0);
		//カメラの位置(視点)をシェーダーに渡す
		cb.vEye = Vector4(0, 0, -10, 0.0f);
		//時間を渡す
		cb.mTime.x = pDesc->mTime;

		memcpy_s(pData.pData, pData.RowPitch, (void*)&cb, sizeof(QuadConstantBuffer));
		pDeviceContext->Unmap(mpConstantBuffer, 0);
	}
	//このコンスタントバッファーを使うシェーダーの登録
	pDeviceContext->VSSetConstantBuffers(0, 1, &mpConstantBuffer);
	pDeviceContext->PSSetConstantBuffers(0, 1, &mpConstantBuffer);

	//設定したあとはスプライトクラスに任せる
	get(pDesc->mID)->render(pDeviceContext);
}

/* End of File *****************************************************/