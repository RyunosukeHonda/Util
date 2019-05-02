/**
* @file OBJStaticMeshRenderer.cpp
* @brief OBJ�`���̃X�^�e�B�b�N���b�V���`��N���X�����t�@�C��
* @author Ryunosuke Honda.
*/
#include "OBJStaticMeshRenderer.h"

#include "ShaderConstantBuffer.h"
#include "ColorConstantBuffer.h"

#include "Camera.h"
#include "DirectionalLightDesc.h"

OBJStaticMeshRenderer::OBJStaticMeshRenderer() :
	base(),
	mpVertexShader(),
	mpVertexLayout(),
	mpPixelShader(),
	mpConstantBuffer0(),
	mpConstantBuffer1()
{
}

OBJStaticMeshRenderer::~OBJStaticMeshRenderer()
{
	SAFE_RELEASE(mpConstantBuffer0);
	SAFE_RELEASE(mpConstantBuffer1);
	SAFE_RELEASE(mpVertexLayout);
	SAFE_RELEASE(mpVertexShader);
	SAFE_RELEASE(mpPixelShader);
}

void OBJStaticMeshRenderer::addMesh(ID3D11Device * pDevice, const OBJMeshID & id, const LPSTR & fileName)
{
	add(id, new OBJStaticMesh(pDevice, fileName));
}

HRESULT OBJStaticMeshRenderer::init(ID3D11Device * pDevice)
{
	//hlsl�t�@�C���ǂݍ��� �u���u�쐬�@�u���u�Ƃ̓V�F�[�_�[�̉�݂����Ȃ��́BXX�V�F�[�_�[�Ƃ��ē����������Ȃ��B��Ŋe��V�F�[�_�[�ɐ��蓾��B
	ID3DBlob *pCompiledShader = NULL;
	ID3DBlob *pErrors = NULL;
	//�u���u����o�[�e�b�N�X�V�F�[�_�[�쐬
	SetShaderDirectory();
	if (FAILED(D3DX10CompileFromFile(L"OBJ_Material_Texture.hlsl", NULL, NULL, "VS", "vs_5_0", 0, 0, NULL, &pCompiledShader, &pErrors, NULL)))
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
	if (FAILED(D3DX11CompileFromFile(L"OBJ_Material_Texture.hlsl", NULL, NULL, "PS", "ps_5_0", 0, 0, NULL, &pCompiledShader, &pErrors, NULL)))
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

	//�R���X�^���g�o�b�t�@�[�쐬(OBJStaticMesh�N���X�p�j�@�ϊ��s��n���p
	D3D11_BUFFER_DESC cb;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.ByteWidth = sizeof(ShaderConstantBuffer);
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.Usage = D3D11_USAGE_DYNAMIC;

	if (FAILED(pDevice->CreateBuffer(&cb, NULL, &mpConstantBuffer0)))
	{
		return E_FAIL;
	}

	//�R���X�^���g�o�b�t�@�[�쐬(OBJStaticMesh�N���X�p�j  �}�e���A���n���p
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.ByteWidth = sizeof(ColorConstantBuffer);
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.Usage = D3D11_USAGE_DYNAMIC;

	if (FAILED(pDevice->CreateBuffer(&cb, NULL, &mpConstantBuffer1)))
	{
		return E_FAIL;
	}

	return S_OK;
}

void OBJStaticMeshRenderer::render(ID3D11DeviceContext * pDeviceContext, const Camera * pCamera, const DirectionalLightDesc & light)
{
	//�g�p����V�F�[�_�[�̓o�^
	pDeviceContext->VSSetShader(mpVertexShader, NULL, 0);
	pDeviceContext->PSSetShader(mpPixelShader, NULL, 0);
	pDeviceContext->GSSetShader(NULL, NULL, 0);

	//���_�C���v�b�g���C�A�E�g���Z�b�g
	pDeviceContext->IASetInputLayout(mpVertexLayout);
	//�v���~�e�B�u�E�g�|���W�[���Z�b�g
	pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	int dataCount = mData.size();
	for (int i = 0; i < dataCount; i++)
	{
		const OBJStaticMeshRenderDesc* pDesc = mData[i];

		//�J�����O���郌�C���[�Ȃ�X�L�b�v
		if (pCamera->isCulling(pDesc->mpTransform->Layer)) continue;

		//���[���h�s��̐ݒ�
		Matrix4x4 world;
		pDesc->mpTransform->makeWorld(&world);

		//�V�F�[�_�[�̃R���X�^���g�o�b�t�@�[�Ɋe��f�[�^��n��
		D3D11_MAPPED_SUBRESOURCE pData;
		if (SUCCEEDED(pDeviceContext->Map(mpConstantBuffer0, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
		{
			ShaderConstantBuffer cb;
			//���[���h�s���n��
			cb.mW = world;
			D3DXMatrixTranspose(&cb.mW, &cb.mW);
			//���[���h�A�J�����A�ˉe�s���n��
			Matrix4x4 m = world * pCamera->getView() *pCamera->getProj();
			cb.mWVP = m;
			D3DXMatrixTranspose(&cb.mWVP, &cb.mWVP);
			//���C�g�̕�����n��
			cb.vLightDir = Vector4(light.direction, 0);
			//���_�ʒu��n��
			cb.vEye = Vector4(pCamera->getLookPt(), 0);

			memcpy_s(pData.pData, pData.RowPitch, (void*)&cb, sizeof(ShaderConstantBuffer));
			pDeviceContext->Unmap(mpConstantBuffer0, 0);
		}

		//���̃R���X�^���g�o�b�t�@�[���g���V�F�[�_�[�̓o�^
		pDeviceContext->VSSetConstantBuffers(0, 1, &mpConstantBuffer0);
		pDeviceContext->PSSetConstantBuffers(0, 1, &mpConstantBuffer0);

		get(pDesc->mID)->render(pDeviceContext, mpConstantBuffer1, pDesc);
	}
}

void OBJStaticMeshRenderer::renderTransparent(ID3D11DeviceContext * pDeviceContext, const Camera * pCamera, const DirectionalLightDesc & light)
{
	//�g�p����V�F�[�_�[�̓o�^
	pDeviceContext->VSSetShader(mpVertexShader, NULL, 0);
	pDeviceContext->PSSetShader(mpPixelShader, NULL, 0);
	pDeviceContext->GSSetShader(NULL, NULL, 0);

	//���_�C���v�b�g���C�A�E�g���Z�b�g
	pDeviceContext->IASetInputLayout(mpVertexLayout);
	//�v���~�e�B�u�E�g�|���W�[���Z�b�g
	pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	int dataCount = mTransparentData.size();
	for (int i = 0; i < dataCount; i++)
	{
		const OBJStaticMeshRenderDesc* pDesc = mTransparentData[i];

		//�J�����O���郌�C���[�Ȃ�X�L�b�v
		if (pCamera->isCulling(pDesc->mpTransform->Layer)) continue;

		//���[���h�s��̐ݒ�
		Matrix4x4 world;
		pDesc->mpTransform->makeWorld(&world);

		//�V�F�[�_�[�̃R���X�^���g�o�b�t�@�[�Ɋe��f�[�^��n��
		D3D11_MAPPED_SUBRESOURCE pData;
		if (SUCCEEDED(pDeviceContext->Map(mpConstantBuffer0, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
		{
			ShaderConstantBuffer cb;
			//���[���h�s���n��
			cb.mW = world;
			D3DXMatrixTranspose(&cb.mW, &cb.mW);
			//���[���h�A�J�����A�ˉe�s���n��
			Matrix4x4 m = world * pCamera->getView() *pCamera->getProj();
			cb.mWVP = m;
			D3DXMatrixTranspose(&cb.mWVP, &cb.mWVP);
			//���C�g�̕�����n��
			cb.vLightDir = Vector4(light.direction, 0);
			//���_�ʒu��n��
			cb.vEye = Vector4(pCamera->getLookPt(), 0);

			memcpy_s(pData.pData, pData.RowPitch, (void*)&cb, sizeof(ShaderConstantBuffer));
			pDeviceContext->Unmap(mpConstantBuffer0, 0);
		}

		//���̃R���X�^���g�o�b�t�@�[���g���V�F�[�_�[�̓o�^
		pDeviceContext->VSSetConstantBuffers(0, 1, &mpConstantBuffer0);
		pDeviceContext->PSSetConstantBuffers(0, 1, &mpConstantBuffer0);

		get(pDesc->mID)->render(pDeviceContext, mpConstantBuffer1, pDesc);
	}
}

/* End of File *****************************************************/