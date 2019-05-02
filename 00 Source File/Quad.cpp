/**
* @file Quad.cpp
* @brief 矩形クラス実装ファイル
* @author Ryunosuke Honda.
*/
#include "Quad.h"

#include "MyVertex.h"
#include <d3dx11.h>

Quad::Quad(ID3D11Device* pDevice, LPCWSTR fileName)
{
	init(pDevice, fileName);
}

Quad::~Quad()
{
	SAFE_RELEASE(mpVertexShader);
	SAFE_RELEASE(mpVertexLayout);
	SAFE_RELEASE(mpPixelShader);
	SAFE_RELEASE(mpVertexBuffer);
}

void Quad::render(ID3D11DeviceContext * pDeviceContext)
{
	//使用するシェーダーの登録	
	pDeviceContext->VSSetShader(mpVertexShader, NULL, 0);
	pDeviceContext->PSSetShader(mpPixelShader, NULL, 0);

	//頂点インプットレイアウトをセット
	pDeviceContext->IASetInputLayout(mpVertexLayout);

	//バーテックスバッファーをセット
	UINT stride = sizeof(MyVertex);
	UINT offset = 0;
	pDeviceContext->IASetVertexBuffers(0, 1, &mpVertexBuffer, &stride, &offset);

	//プリミティブをレンダリング
	pDeviceContext->Draw(4, 0);
}

void Quad::init(ID3D11Device * pDevice, LPCWSTR fileName)
{
	SetShaderDirectory();
	//hlslファイル読み込み ブロブ作成　ブロブとはシェーダーの塊みたいなもの。XXシェーダーとして特徴を持たない。後で各種シェーダーに成り得る。
	ID3D10Blob *pCompiledShader = NULL;
	ID3D10Blob *pErrors = NULL;
	//ブロブからバーテックスシェーダー作成
	if (FAILED(D3DX11CompileFromFile(fileName, NULL, NULL, "VS", "vs_5_0", 0, 0, NULL, &pCompiledShader, &pErrors, NULL)))
	{
		MessageBox(0, L"hlsl読み込み失敗", NULL, MB_OK);
		return;
	}
	SAFE_RELEASE(pErrors);

	if (FAILED(pDevice->CreateVertexShader(pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), NULL, &mpVertexShader)))
	{
		SAFE_RELEASE(pCompiledShader);
		MessageBox(0, L"バーテックスシェーダー作成失敗", NULL, MB_OK);
		return;
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
		return;
	}

	//ブロブからピクセルシェーダー作成
	if (FAILED(D3DX11CompileFromFile(fileName, NULL, NULL, "PS", "ps_5_0", 0, 0, NULL, &pCompiledShader, &pErrors, NULL)))
	{
		MessageBox(0, L"hlsl読み込み失敗", NULL, MB_OK);
		return;
	}
	SAFE_RELEASE(pErrors);
	if (FAILED(pDevice->CreatePixelShader(pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), NULL, &mpPixelShader)))
	{
		SAFE_RELEASE(pCompiledShader);
		MessageBox(0, L"ピクセルシェーダー作成失敗", NULL, MB_OK);
		return;
	}
	SAFE_RELEASE(pCompiledShader);

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
}

/* End of File *****************************************************/