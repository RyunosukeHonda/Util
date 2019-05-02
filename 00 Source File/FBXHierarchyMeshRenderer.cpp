/**
* @file FBXHierarchyMeshRenderer.cpp
* @brief FBX�K�w���b�V���`��N���X�����t�@�C��
* @author Ryunosuke Honda.
*/
#include "FBXHierarchyMeshRenderer.h"
#include "ShaderLightEyevec.h"
#include "ShaderWorldColor.h"
#include "Camera.h"
#include <d3dx11.h>

FBXHierarchyMeshRenderer::FBXHierarchyMeshRenderer():
	base(),
	mpVertexShader(),
	mpVertexLayout(),
	mpPixelShader(),
	mpConstantBuffer0(),
	mpConstantBuffer1(),
	mpConstantBuffer2()
{
}

FBXHierarchyMeshRenderer::~FBXHierarchyMeshRenderer()
{
}

HRESULT FBXHierarchyMeshRenderer::init(ID3D11Device * pDevice)
{
	//hlsl�t�@�C���ǂݍ��� �u���u�쐬�@�u���u�Ƃ̓V�F�[�_�[�̉�݂����Ȃ��́BXX�V�F�[�_�[�Ƃ��ē����������Ȃ��B��Ŋe��V�F�[�_�[�ɐ��蓾��B
	ID3DBlob *pCompiledShader = NULL;
	ID3DBlob *pErrors = NULL;
	//�u���u����o�[�e�b�N�X�V�F�[�_�[�쐬
	if (FAILED(D3DX11CompileFromFile(L"FBXHierarchy_Material_Texture.hlsl", NULL, NULL, "VS", "vs_5_0", 0, 0, NULL, &pCompiledShader, &pErrors, NULL)))
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
	if (FAILED(D3DX11CompileFromFile(L"FBXHierarchy_Material_Texture.hlsl", NULL, NULL, "PS", "ps_5_0", 0, 0, NULL, &pCompiledShader, &pErrors, NULL)))
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
	//�R���X�^���g�o�b�t�@�[0�쐬 ���C�g�Ǝ��_�@�n���p
	D3D11_BUFFER_DESC cb;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.ByteWidth = sizeof(ShaderLightEyevec);
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;
	cb.Usage = D3D11_USAGE_DYNAMIC;

	if (FAILED(pDevice->CreateBuffer(&cb, NULL, &mpConstantBuffer0)))
	{
		return E_FAIL;
	}
	//�R���X�^���g�o�b�t�@�[1�쐬  FBXMesh���Ŏg�p �ϊ��s��ƃ}�e���A���p
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.ByteWidth = sizeof(ShaderWorldColor);
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;
	cb.Usage = D3D11_USAGE_DYNAMIC;

	if (FAILED(pDevice->CreateBuffer(&cb, NULL, &mpConstantBuffer1)))
	{
		return E_FAIL;
	}
	return S_OK;
}

void FBXHierarchyMeshRenderer::addMesh(ID3D11Device * pDevice, const FBXHierarchyID & id, const LPSTR & fileName)
{
	add(id, new FBXHierarchyMesh(pDevice, fileName));
}

void FBXHierarchyMeshRenderer::render(ID3D11DeviceContext * pDeviceContext, const Camera* pCamera, const DirectionalLightDesc& light)
{
	////�g�p����V�F�[�_�[�̓o�^	
	pDeviceContext->VSSetShader(mpVertexShader, NULL, 0);
	pDeviceContext->PSSetShader(mpPixelShader, NULL, 0);
	//���_�C���v�b�g���C�A�E�g���Z�b�g
	pDeviceContext->IASetInputLayout(mpVertexLayout);

	int dataCount = mData.size();
	for (int i = 0; i < dataCount; i++)
	{
		const FBXHierarchyMeshRenderDesc* pDesc = mData[i];

		//�J�����O���郌�C���[�Ȃ�X�L�b�v
		if (pCamera->isCulling(pDesc->mpTransform->Layer)) continue;

		//�V�F�[�_�[�̃R���X�^���g�o�b�t�@�[�Ɋe��f�[�^��n��	
		D3D11_MAPPED_SUBRESOURCE pData;
		if (SUCCEEDED(pDeviceContext->Map(mpConstantBuffer0, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
		{
			ShaderLightEyevec cb;
			//���C�g�̕�����n��
			D3DXVECTOR3 vLightDir(0, 0, -1);
			D3DXVec3Normalize(&vLightDir, &vLightDir);
			cb.vLightDir = D3DXVECTOR4(vLightDir.x, vLightDir.y, vLightDir.z, 0.0f);
			//���_�ʒu��n��
			cb.vEye = Vector4(pCamera->getLookPt(), 0);

			memcpy_s(pData.pData, pData.RowPitch, (void*)&cb, sizeof(ShaderLightEyevec));
			pDeviceContext->Unmap(mpConstantBuffer0, 0);
		}
		pDeviceContext->VSSetConstantBuffers(0, 1, &mpConstantBuffer0);
		pDeviceContext->PSSetConstantBuffers(0, 1, &mpConstantBuffer0);

		//���b�V���������_�����O
		get(pDesc->mID)->render(pDeviceContext, mpConstantBuffer1, pCamera, pDesc);
	}
}

void FBXHierarchyMeshRenderer::renderTransparent(ID3D11DeviceContext * pDeviceContext, const Camera * pCamera, const DirectionalLightDesc & light)
{
	////�g�p����V�F�[�_�[�̓o�^	
	pDeviceContext->VSSetShader(mpVertexShader, NULL, 0);
	pDeviceContext->PSSetShader(mpPixelShader, NULL, 0);
	//���_�C���v�b�g���C�A�E�g���Z�b�g
	pDeviceContext->IASetInputLayout(mpVertexLayout);

	int dataCount = mTransparentData.size();
	for (int i = 0; i < dataCount; i++)
	{
		const FBXHierarchyMeshRenderDesc* pDesc = mTransparentData[i];

		//�J�����O���郌�C���[�Ȃ�X�L�b�v
		if (pCamera->isCulling(pDesc->mpTransform->Layer)) continue;

		//�V�F�[�_�[�̃R���X�^���g�o�b�t�@�[�Ɋe��f�[�^��n��	
		D3D11_MAPPED_SUBRESOURCE pData;
		if (SUCCEEDED(pDeviceContext->Map(mpConstantBuffer0, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
		{
			ShaderLightEyevec cb;
			//���C�g�̕�����n��
			D3DXVECTOR3 vLightDir(0, 0, -1);
			D3DXVec3Normalize(&vLightDir, &vLightDir);
			cb.vLightDir = D3DXVECTOR4(vLightDir.x, vLightDir.y, vLightDir.z, 0.0f);
			//���_�ʒu��n��
			cb.vEye = Vector4(pCamera->getLookPt(), 0);

			memcpy_s(pData.pData, pData.RowPitch, (void*)&cb, sizeof(ShaderLightEyevec));
			pDeviceContext->Unmap(mpConstantBuffer0, 0);
		}
		pDeviceContext->VSSetConstantBuffers(0, 1, &mpConstantBuffer0);
		pDeviceContext->PSSetConstantBuffers(0, 1, &mpConstantBuffer0);

		//���b�V���������_�����O
		get(pDesc->mID)->render(pDeviceContext, mpConstantBuffer1, pCamera, pDesc);
	}
}

/* End of File *****************************************************/