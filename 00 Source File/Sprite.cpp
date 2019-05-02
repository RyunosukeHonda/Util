/**
* @file Sprite.cpp
* @brief �X�v���C�g�N���X�����t�@�C��
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
	//�o�[�e�b�N�X�o�b�t�@�[���Z�b�g
	UINT stride = sizeof(MyVertex);
	UINT offset = 0;
	pDeviceContext->IASetVertexBuffers(0, 1, &mpVertexBuffer, &stride, &offset);

	//�e�N�X�`���[���V�F�[�_�[�ɓn��
	pDeviceContext->PSSetSamplers(0, 1, &mpSampleLinear);
	pDeviceContext->PSSetShaderResources(0, 1, &mpTexture);

	//�v���~�e�B�u�������_�����O
	pDeviceContext->Draw(4, 0);
}

void Sprite::init(ID3D11Device * pDevice, LPCWSTR fileName)
{
	//�o�[�e�b�N�X�o�b�t�@�[�쐬
	MyVertex vertices[] =
	{
		D3DXVECTOR3(-0.5,-0.5,0),D3DXVECTOR3(0,0,-1),D3DXVECTOR2(0,1),//���_1,
		D3DXVECTOR3(-0.5,0.5,0), D3DXVECTOR3(0,0,-1),D3DXVECTOR2(0,0),//���_2
		D3DXVECTOR3(0.5,-0.5,0),D3DXVECTOR3(0,0,-1),D3DXVECTOR2(1,1),  //���_3
		D3DXVECTOR3(0.5,0.5,0),D3DXVECTOR3(0,0,-1),D3DXVECTOR2(1,0) //���_4	
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
		MessageBox(0, L"�o�b�t�@�쐬���s", NULL, MB_OK);
		return;
	}

	//�e�N�X�`���[�p�T���v���[�쐬
	D3D11_SAMPLER_DESC SamDesc;
	ZeroMemory(&SamDesc, sizeof(D3D11_SAMPLER_DESC));
	SamDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	SamDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	pDevice->CreateSamplerState(&SamDesc, &mpSampleLinear);

	//�e�N�X�`���[�쐬
	SetVisualDirectory();
	if (FAILED(D3DX11CreateShaderResourceViewFromFile(pDevice, fileName, NULL, NULL, &mpTexture, NULL)))
	{
		MessageBox(0, L"�e�N�X�`���[�ǂݍ��ݎ��s", NULL, MB_OK);
		return;
	}
}

/* End of File *****************************************************/