/**
* @file Sprite.cpp
* @brief スプライトクラス実装ファイル
* @author Ryunosuke Honda.
*/
#include "Sprite.h"
#include "MyVertex.h"

#include <d3dx11.h>


Sprite::Sprite(ID3D11Device * pDevice, LPCWSTR fileName) :
	mpSampleLinear(nullptr),
	mpTexture(nullptr),
	mpVertexBuffer(nullptr)
{
	init(pDevice, fileName);
}

Sprite::~Sprite()
{
	SAFE_RELEASE(mpSampleLinear);
	SAFE_RELEASE(mpTexture);
	SAFE_RELEASE(mpVertexBuffer);
}

void Sprite::render(ID3D11DeviceContext * pDeviceContext)
{
	//バーテックスバッファーをセット
	UINT stride = sizeof(MyVertex);
	UINT offset = 0;
	pDeviceContext->IASetVertexBuffers(0, 1, &mpVertexBuffer, &stride, &offset);

	//テクスチャーをシェーダーに渡す
	pDeviceContext->PSSetSamplers(0, 1, &mpSampleLinear);
	pDeviceContext->PSSetShaderResources(0, 1, &mpTexture);

	//プリミティブをレンダリング
	pDeviceContext->Draw(4, 0);
}

void Sprite::init(ID3D11Device * pDevice, LPCWSTR fileName)
{
	//バーテックスバッファー作成
	MyVertex vertices[] =
	{
		D3DXVECTOR3(-0.5,-0.5,0),D3DXVECTOR3(0,0,-1),D3DXVECTOR2(0,1),//頂点1,
		D3DXVECTOR3(-0.5,0.5,0), D3DXVECTOR3(0,0,-1),D3DXVECTOR2(0,0),//頂点2
		D3DXVECTOR3(0.5,-0.5,0),D3DXVECTOR3(0,0,-1),D3DXVECTOR2(1,1),  //頂点3
		D3DXVECTOR3(0.5,0.5,0),D3DXVECTOR3(0,0,-1),D3DXVECTOR2(1,0) //頂点4	
	};
	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(MyVertex) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA data;
	data.pSysMem = vertices;
	if (FAILED(pDevice->CreateBuffer(&bd, &data, &mpVertexBuffer)))
	{
		MessageBox(0, L"バッファ作成失敗", NULL, MB_OK);
		return;
	}

	//テクスチャー用サンプラー作成
	D3D11_SAMPLER_DESC SamDesc;
	ZeroMemory(&SamDesc, sizeof(D3D11_SAMPLER_DESC));
	SamDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	SamDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	pDevice->CreateSamplerState(&SamDesc, &mpSampleLinear);

	//テクスチャー作成
	SetVisualDirectory();
	if (FAILED(D3DX11CreateShaderResourceViewFromFile(pDevice, fileName, NULL, NULL, &mpTexture, NULL)))
	{
		MessageBox(0, L"テクスチャー読み込み失敗", NULL, MB_OK);
		return;
	}
}

/* End of File *****************************************************/