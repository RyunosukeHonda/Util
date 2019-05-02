/**
* @file SpriteRenderer.cpp
* @brief �X�v���C�g�Ǘ��N���X�����t�@�C��
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
	//hlsl�t�@�C���ǂݍ��� �u���u�쐬�@�u���u�Ƃ̓V�F�[�_�[�̉�݂����Ȃ��́BXX�V�F�[�_�[�Ƃ��ē����������Ȃ��B��Ŋe��V�F�[�_�[�ɐ��蓾��B
	ID3D10Blob *pCompiledShader = NULL;
	ID3D10Blob *pErrors = NULL;
	//�u���u����o�[�e�b�N�X�V�F�[�_�[�쐬
	if (FAILED(D3DX11CompileFromFile(L"Sprite_Material_Texture.hlsl", NULL, NULL, "VS", "vs_5_0", 0, 0, NULL, &pCompiledShader, &pErrors, NULL)))
	{
		MessageBox(0, L"hlsl�ǂݍ��ݎ��s", NULL, MB_OK);
		return E_FAIL;
	}
	SAFE_RELEASE(pErrors);

	if (FAILED(pDevice->CreateVertexShader(pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), NULL, &mpVertexShader)))
	{
		SAFE_RELEASE(pCompiledShader);
		MessageBox(0, L"�o�[�e�b�N�X�V�F�[�_�[�쐬���s", NULL, MB_OK);
		return E_FAIL;
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
		return FALSE;
	}
	//�u���u����s�N�Z���V�F�[�_�[�쐬
	if (FAILED(D3DX11CompileFromFile(L"Sprite_Material_Texture.hlsl", NULL, NULL, "PS", "ps_5_0", 0, 0, NULL, &pCompiledShader, &pErrors, NULL)))
	{
		MessageBox(0, L"hlsl�ǂݍ��ݎ��s", NULL, MB_OK);
		return E_FAIL;
	}
	SAFE_RELEASE(pErrors);
	if (FAILED(pDevice->CreatePixelShader(pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), NULL, &mpPixelShader)))
	{
		SAFE_RELEASE(pCompiledShader);
		MessageBox(0, L"�s�N�Z���V�F�[�_�[�쐬���s", NULL, MB_OK);
		return E_FAIL;
	}
	SAFE_RELEASE(pCompiledShader);

	//�R���X�^���g�o�b�t�@�[�쐬
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
	//�ȈՂ̂��ߋL�q�q�̃f�B�t���[�Y�F�̃A���t�@�l�Ŕ���
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
	//�`��ݒ��K�p
	initRenderConfig(pDeviceContext);

	//�S�f�[�^�̕`��
	for (int i = 0; i < mUIData.size(); i++)
	{
		renderUIImage(mUIData[i], pDeviceContext, UIMatrix);
	}
}

void SpriteRenderer::renderTransparentUI(ID3D11DeviceContext * pDeviceContext, const Matrix4x4 & UIMatrix)
{
	//�`��ݒ��K�p
	initRenderConfig(pDeviceContext);

	//�S�f�[�^�̕`��
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
	//�`��ݒ��K�p
	initRenderConfig(pDeviceContext);

	//�S�f�[�^�̕`��
	for (int i = 0; i < mData.size(); i++)
	{
		renderSprite(mData[i], pDeviceContext, pCamera, light);
	}
}

void SpriteRenderer::renderTransparent(ID3D11DeviceContext * pDeviceContext, const Camera * pCamera, const DirectionalLightDesc & light)
{
	//�`��ݒ��K�p
	initRenderConfig(pDeviceContext);

	//�S�f�[�^�̕`��
	for (int i = 0; i < mTransparentData.size(); i++)
	{
		renderSprite(mTransparentData[i], pDeviceContext, pCamera, light);
	}
}

void SpriteRenderer::initRenderConfig(ID3D11DeviceContext * pDeviceContext)
{
	//�g�p����V�F�[�_�[�̓o�^	
	pDeviceContext->VSSetShader(mpVertexShader, NULL, 0);
	pDeviceContext->PSSetShader(mpPixelShader, NULL, 0);

	//���_�C���v�b�g���C�A�E�g���Z�b�g
	pDeviceContext->IASetInputLayout(mpVertexLayout);

	//�v���~�e�B�u�E�g�|���W�[���Z�b�g
	pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
}

void SpriteRenderer::renderSprite(const SpriteRenderDesc * pDesc, ID3D11DeviceContext * pDeviceContext, const Camera * pCamera, const DirectionalLightDesc & light)
{
	//�J�����O���郌�C���[�Ȃ�X�L�b�v
	if (pCamera->isCulling(pDesc->mpTransform->Layer)) return;

	//�V�F�[�_�[�̃R���X�^���g�o�b�t�@�[�Ɋe��f�[�^��n��	
	D3D11_MAPPED_SUBRESOURCE pData;
	if (SUCCEEDED(pDeviceContext->Map(mpConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
	{
		SpriteConstantBuffer cb;
		//���[���h�s��̐ݒ�
		Matrix4x4 world;
		pDesc->mpTransform->makeWorld(&world);
		//���[���h�s���n��
		cb.mW = world;
		D3DXMatrixTranspose(&cb.mW, &cb.mW);
		//���[���h�A�J�����A�ˉe�s���n��
		Matrix4x4 m = world * pCamera->getView() * pCamera->getProj();
		cb.mWVP = m;
		D3DXMatrixTranspose(&cb.mWVP, &cb.mWVP);
		//�J���[��n�� 
		cb.mColor = pDesc->mDiffuse;
		//���C�g������n��
		cb.vLightDir = Vector4(light.direction, 0);
		//�J�����̈ʒu(���_)���V�F�[�_�[�ɓn��
		cb.vEye = Vector4(pCamera->getLookPt(), 0.0f);

		memcpy_s(pData.pData, pData.RowPitch, (void*)&cb, sizeof(SpriteConstantBuffer));
		pDeviceContext->Unmap(mpConstantBuffer, 0);
	}

	//���̃R���X�^���g�o�b�t�@�[���g���V�F�[�_�[�̓o�^
	pDeviceContext->VSSetConstantBuffers(0, 1, &mpConstantBuffer);
	pDeviceContext->PSSetConstantBuffers(0, 1, &mpConstantBuffer);

	//�ݒ肵�����Ƃ̓X�v���C�g�N���X�ɔC����
	get(pDesc->mID)->render(pDeviceContext);
}

void SpriteRenderer::renderUIImage(const UIImageRenderDesc * pDesc, ID3D11DeviceContext * pDeviceContext, const Matrix4x4 & UIMatrix)
{
	//���[���h�ϊ�
	Matrix4x4 world;
	pDesc->mpRect->makeWorld(&world);

	//�V�F�[�_�[�̃R���X�^���g�o�b�t�@�[�Ɋe��f�[�^��n��	
	D3D11_MAPPED_SUBRESOURCE pData;
	if (SUCCEEDED(pDeviceContext->Map(mpConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
	{
		SpriteConstantBuffer cb;
		//���[���h�s���n��
		cb.mW = world;
		D3DXMatrixTranspose(&cb.mW, &cb.mW);
		//���[���h���W��UI���W�n�ɕϊ����ēn��
		Matrix4x4 m = world * UIMatrix;
		cb.mWVP = m;
		D3DXMatrixTranspose(&cb.mWVP, &cb.mWVP);
		//�J���[��n�� 
		cb.mColor = pDesc->mDiffuse;
		//���C�g������n��
		cb.vLightDir = Vector4(1, 1, 1, 1);
		//�J�����̈ʒu(���_)���V�F�[�_�[�ɓn��
		cb.vEye = Vector4(0, 0, -10, 0);

		memcpy_s(pData.pData, pData.RowPitch, (void*)&cb, sizeof(SpriteConstantBuffer));
		pDeviceContext->Unmap(mpConstantBuffer, 0);
	}
	//���̃R���X�^���g�o�b�t�@�[���g���V�F�[�_�[�̓o�^
	pDeviceContext->VSSetConstantBuffers(0, 1, &mpConstantBuffer);
	pDeviceContext->PSSetConstantBuffers(0, 1, &mpConstantBuffer);

	//�ݒ肵�����Ƃ̓X�v���C�g�N���X�ɔC����
	get(pDesc->mID)->render(pDeviceContext);
}

/* End of File *****************************************************/