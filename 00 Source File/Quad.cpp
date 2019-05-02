/**
* @file Quad.cpp
* @brief ��`�N���X�����t�@�C��
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
	//�g�p����V�F�[�_�[�̓o�^	
	pDeviceContext->VSSetShader(mpVertexShader, NULL, 0);
	pDeviceContext->PSSetShader(mpPixelShader, NULL, 0);

	//���_�C���v�b�g���C�A�E�g���Z�b�g
	pDeviceContext->IASetInputLayout(mpVertexLayout);

	//�o�[�e�b�N�X�o�b�t�@�[���Z�b�g
	UINT stride = sizeof(MyVertex);
	UINT offset = 0;
	pDeviceContext->IASetVertexBuffers(0, 1, &mpVertexBuffer, &stride, &offset);

	//�v���~�e�B�u�������_�����O
	pDeviceContext->Draw(4, 0);
}

void Quad::init(ID3D11Device * pDevice, LPCWSTR fileName)
{
	SetShaderDirectory();
	//hlsl�t�@�C���ǂݍ��� �u���u�쐬�@�u���u�Ƃ̓V�F�[�_�[�̉�݂����Ȃ��́BXX�V�F�[�_�[�Ƃ��ē����������Ȃ��B��Ŋe��V�F�[�_�[�ɐ��蓾��B
	ID3D10Blob *pCompiledShader = NULL;
	ID3D10Blob *pErrors = NULL;
	//�u���u����o�[�e�b�N�X�V�F�[�_�[�쐬
	if (FAILED(D3DX11CompileFromFile(fileName, NULL, NULL, "VS", "vs_5_0", 0, 0, NULL, &pCompiledShader, &pErrors, NULL)))
	{
		MessageBox(0, L"hlsl�ǂݍ��ݎ��s", NULL, MB_OK);
		return;
	}
	SAFE_RELEASE(pErrors);

	if (FAILED(pDevice->CreateVertexShader(pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), NULL, &mpVertexShader)))
	{
		SAFE_RELEASE(pCompiledShader);
		MessageBox(0, L"�o�[�e�b�N�X�V�F�[�_�[�쐬���s", NULL, MB_OK);
		return;
	}
	//���_�C���v�b�g���C�A�E�g���`	
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = sizeof(layout) / sizeof(layout[0]);
	//���_�C���v�b�g���C�A�E�g���쐬
	if (FAILED(pDevice->CreateInputLayout(layout, numElements, pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), &mpVertexLayout)))
	{
		return;
	}

	//�u���u����s�N�Z���V�F�[�_�[�쐬
	if (FAILED(D3DX11CompileFromFile(fileName, NULL, NULL, "PS", "ps_5_0", 0, 0, NULL, &pCompiledShader, &pErrors, NULL)))
	{
		MessageBox(0, L"hlsl�ǂݍ��ݎ��s", NULL, MB_OK);
		return;
	}
	SAFE_RELEASE(pErrors);
	if (FAILED(pDevice->CreatePixelShader(pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), NULL, &mpPixelShader)))
	{
		SAFE_RELEASE(pCompiledShader);
		MessageBox(0, L"�s�N�Z���V�F�[�_�[�쐬���s", NULL, MB_OK);
		return;
	}
	SAFE_RELEASE(pCompiledShader);

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
}

/* End of File *****************************************************/