/**
* @file QuadRenderer.cpp
* @brief �l�p�`�|���S���`��N���X�����t�@�C��
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

void QuadRenderer::renderUI(ID3D11DeviceContext * pDeviceContext, const Matrix4x4& UIMatrix)
{
	//�`��ݒ��K�p
	initRenderConfig(pDeviceContext);

	//�S�f�[�^�̕`��
	for (int i = 0; i < mUIData.size(); i++)
	{
		renderUIQuad(mUIData[i], pDeviceContext, UIMatrix);
	}
}

void QuadRenderer::renderTransparentUI(ID3D11DeviceContext * pDeviceContext, const Matrix4x4 & UIMatrix)
{
	//�`��ݒ��K�p
	initRenderConfig(pDeviceContext);

	//�S�f�[�^�̕`��
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
	//�R���X�^���g�o�b�t�@�[�쐬
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
	//�`��ݒ��K�p
	initRenderConfig(pDeviceContext);

	//�S�f�[�^�̕`��
	for (int i = 0; i < mData.size(); i++)
	{
		renderQuad(mData[i], pDeviceContext, pCamera, light);
	}
}

void QuadRenderer::renderTransparent(ID3D11DeviceContext * pDeviceContext, const Camera * pCamera, const DirectionalLightDesc & light)
{
	//�`��ݒ��K�p
	initRenderConfig(pDeviceContext);

	//�S�f�[�^�̕`��
	for (int i = 0; i < mTransparentData.size(); i++)
	{
		renderQuad(mTransparentData[i], pDeviceContext, pCamera, light);
	}
}

void QuadRenderer::initRenderConfig(ID3D11DeviceContext * pDeviceContext)
{
	//�v���~�e�B�u�E�g�|���W�[���Z�b�g
	pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
}

void QuadRenderer::renderQuad(const QuadRenderDesc * pDesc, ID3D11DeviceContext * pDeviceContext, const Camera * pCamera, const DirectionalLightDesc & light)
{
	//�J�����O���郌�C���[�Ȃ�X�L�b�v
	if (pCamera->isCulling(pDesc->mpTransform->Layer)) return;

	//���[���h�s��̐ݒ�
	Matrix4x4 world;
	pDesc->mpTransform->makeWorld(&world);

	//�V�F�[�_�[�̃R���X�^���g�o�b�t�@�[�Ɋe��f�[�^��n��	
	D3D11_MAPPED_SUBRESOURCE pData;
	if (SUCCEEDED(pDeviceContext->Map(mpConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
	{
		QuadConstantBuffer cb;
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
		//���Ԃ�n��
		cb.mTime.x = pDesc->mTime;

		memcpy_s(pData.pData, pData.RowPitch, (void*)&cb, sizeof(QuadConstantBuffer));
		pDeviceContext->Unmap(mpConstantBuffer, 0);
	}
	//���̃R���X�^���g�o�b�t�@�[���g���V�F�[�_�[�̓o�^
	pDeviceContext->VSSetConstantBuffers(0, 1, &mpConstantBuffer);
	pDeviceContext->PSSetConstantBuffers(0, 1, &mpConstantBuffer);

	//�ݒ肵�����Ƃ̓X�v���C�g�N���X�ɔC����
	get(pDesc->mID)->render(pDeviceContext);
}

void QuadRenderer::renderUIQuad(const UIQuadRenderDesc * pDesc, ID3D11DeviceContext * pDeviceContext, const Matrix4x4 & UIMatrix)
{
	//���[���h�ϊ�
	Matrix4x4 world;
	pDesc->mpRect->makeWorld(&world);

	//�V�F�[�_�[�̃R���X�^���g�o�b�t�@�[�Ɋe��f�[�^��n��	
	D3D11_MAPPED_SUBRESOURCE pData;
	if (SUCCEEDED(pDeviceContext->Map(mpConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
	{
		QuadConstantBuffer cb;
		//���[���h�s���n��
		cb.mW = world;
		D3DXMatrixTranspose(&cb.mW, &cb.mW);
		//���[���h�A�J�����A�ˉe�s���n��
		Matrix4x4 m = world * UIMatrix;
		cb.mWVP = m;
		D3DXMatrixTranspose(&cb.mWVP, &cb.mWVP);
		//�J���[��n�� 
		cb.mColor = pDesc->mDiffuse;
		//���C�g������n��
		cb.vLightDir = Vector4(1, 1, 1, 0);
		//�J�����̈ʒu(���_)���V�F�[�_�[�ɓn��
		cb.vEye = Vector4(0, 0, -10, 0.0f);
		//���Ԃ�n��
		cb.mTime.x = pDesc->mTime;

		memcpy_s(pData.pData, pData.RowPitch, (void*)&cb, sizeof(QuadConstantBuffer));
		pDeviceContext->Unmap(mpConstantBuffer, 0);
	}
	//���̃R���X�^���g�o�b�t�@�[���g���V�F�[�_�[�̓o�^
	pDeviceContext->VSSetConstantBuffers(0, 1, &mpConstantBuffer);
	pDeviceContext->PSSetConstantBuffers(0, 1, &mpConstantBuffer);

	//�ݒ肵�����Ƃ̓X�v���C�g�N���X�ɔC����
	get(pDesc->mID)->render(pDeviceContext);
}

/* End of File *****************************************************/