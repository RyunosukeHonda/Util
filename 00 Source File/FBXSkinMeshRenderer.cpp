/**
* @file FBXSkinMeshRenderer.cpp
* @brief FBX�X�L�����b�V���Ǘ��N���X�����t�@�C��
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
	//�u���u����o�[�e�b�N�X�V�F�[�_�[�쐬
	ID3DBlob *pCompiledShader = NULL;
	ID3DBlob *pErrors = NULL;
	SetShaderDirectory();
	if (FAILED(D3DX11CompileFromFile(L"FBXSkin_Material_Texture.hlsl", NULL, NULL, "VSSkin", "vs_5_0", 0, 0, NULL, &pCompiledShader, &pErrors, NULL)))
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
	D3D11_INPUT_ELEMENT_DESC layout_Skin[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "BONE_INDEX", 0, DXGI_FORMAT_R32G32B32A32_UINT, 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "BONE_WEIGHT", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 48, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = sizeof(layout_Skin) / sizeof(layout_Skin[0]);
	//���_�C���v�b�g���C�A�E�g���쐬
	if (FAILED(pDevice->CreateInputLayout(layout_Skin, numElements, pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), &mpVertexLayout)))
	{
		return FALSE;
	}
	//�u���u����s�N�Z���V�F�[�_�[�쐬
	if (FAILED(D3DX11CompileFromFile(L"FBXSkin_Material_Texture.hlsl", NULL, NULL, "PSSkin", "ps_5_0", 0, 0, NULL, &pCompiledShader, &pErrors, NULL)))
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

	//�R���X�^���g�o�b�t�@�[�쐬  (FBXSkinMesh�N���X�p�j���C�g�A���_�n���p
	D3D11_BUFFER_DESC cb;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.ByteWidth = sizeof(ShaderLightEyevec);
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;
	cb.Usage = D3D11_USAGE_DYNAMIC;
	if (FAILED(pDevice->CreateBuffer(&cb, NULL, &mpConstantBuffer0)))
	{
		MessageBox(0, L"�R���X�^���g�o�b�t�@�[0�쐬���s", NULL, MB_OK);
		return E_FAIL;
	}

	//�R���X�^���g�o�b�t�@�[�쐬  (FBXSkinMesh�N���X�p�j�ϊ��s��A�}�e���A���n���p
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.ByteWidth = sizeof(ShaderWorldColor);
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;
	cb.Usage = D3D11_USAGE_DYNAMIC;
	if (FAILED(pDevice->CreateBuffer(&cb, NULL, &mpConstantBuffer1)))
	{
		MessageBox(0, L"�R���X�^���g�o�b�t�@�[1�쐬���s", NULL, MB_OK);
		return E_FAIL;
	}

	//�R���X�^���g�o�b�t�@�[�쐬   (FBXSkinMesh�N���X�p�j�{�[���p
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
	//�o�^����Ă��Ȃ���ΐV�K�ɓo�^
	add(id, new FBXSkinMesh(pDevice, fileName));
}

void FBXSkinMeshRenderer::render(ID3D11DeviceContext* pDeviceContext, const Camera* pCamera, const DirectionalLightDesc & light)
{
	////�g�p����V�F�[�_�[�̓o�^	
	pDeviceContext->VSSetShader(mpVertexShader, NULL, 0);
	pDeviceContext->PSSetShader(mpPixelShader, NULL, 0);

	//���_�C���v�b�g���C�A�E�g���Z�b�g
	pDeviceContext->IASetInputLayout(mpVertexLayout);

	int dataCount = mData.size();
	for (int i = 0; i < dataCount; i++)
	{
		const FBXSkinMeshRenderDesc* pDesc = mData[i];

		//�J�����O���郌�C���[�Ȃ�X�L�b�v
		if (pCamera->isCulling(pDesc->mpTransform->Layer)) continue;

		//�V�F�[�_�[�̃R���X�^���g�o�b�t�@�[�Ɋe��f�[�^��n��	
		D3D11_MAPPED_SUBRESOURCE pData;
		if (SUCCEEDED(pDeviceContext->Map(mpConstantBuffer0, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
		{
			ShaderLightEyevec cb;
			//���C�g�̕�����n��
			cb.vLightDir = Vector4(light.direction, 0);
			//���_�ʒu��n��
			cb.vEye = Vector4(pCamera->getLookPt(), 0);

			memcpy_s(pData.pData, pData.RowPitch, (void*)&cb, sizeof(ShaderLightEyevec));
			pDeviceContext->Unmap(mpConstantBuffer0, 0);
		}
		pDeviceContext->VSSetConstantBuffers(0, 1, &mpConstantBuffer0);
		//�A�j���[�V�����t���[����i�߂�@�X�L�����X�V
		FBXSkinMesh* mesh = get(pDesc->mID).get();
		mesh->setNewPoseMatrices(pDesc->mFrame);
		pDeviceContext->PSSetConstantBuffers(0, 1, &mpConstantBuffer0);

		//�t���[����i�߂����Ƃɂ��ω������|�[�Y�i�{�[���̍s��j���V�F�[�_�[�ɓn��
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
	////�g�p����V�F�[�_�[�̓o�^	
	pDeviceContext->VSSetShader(mpVertexShader, NULL, 0);
	pDeviceContext->PSSetShader(mpPixelShader, NULL, 0);

	//���_�C���v�b�g���C�A�E�g���Z�b�g
	pDeviceContext->IASetInputLayout(mpVertexLayout);

	int dataCount = mTransparentData.size();
	for (int i = 0; i < dataCount; i++)
	{
		const FBXSkinMeshRenderDesc* pDesc = mTransparentData[i];

		//�J�����O���郌�C���[�Ȃ�X�L�b�v
		if (pCamera->isCulling(pDesc->mpTransform->Layer)) continue;

		//�V�F�[�_�[�̃R���X�^���g�o�b�t�@�[�Ɋe��f�[�^��n��	
		D3D11_MAPPED_SUBRESOURCE pData;
		if (SUCCEEDED(pDeviceContext->Map(mpConstantBuffer0, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
		{
			ShaderLightEyevec cb;
			//���C�g�̕�����n��
			cb.vLightDir = Vector4(light.direction, 0);
			//���_�ʒu��n��
			cb.vEye = Vector4(pCamera->getLookPt(), 0);

			memcpy_s(pData.pData, pData.RowPitch, (void*)&cb, sizeof(ShaderLightEyevec));
			pDeviceContext->Unmap(mpConstantBuffer0, 0);
		}
		pDeviceContext->VSSetConstantBuffers(0, 1, &mpConstantBuffer0);
		//�A�j���[�V�����t���[����i�߂�@�X�L�����X�V
		FBXSkinMesh* mesh = get(pDesc->mID).get();
		mesh->setNewPoseMatrices(pDesc->mFrame);
		pDeviceContext->PSSetConstantBuffers(0, 1, &mpConstantBuffer0);

		//�t���[����i�߂����Ƃɂ��ω������|�[�Y�i�{�[���̍s��j���V�F�[�_�[�ɓn��
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