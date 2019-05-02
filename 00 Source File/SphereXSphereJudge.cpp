/**
* @file SphereXSphereJudge.cpp
* @brief ���E�����m�̏Փ˔���N���X�����t�@�C��
* @author Ryunosuke Honda.
*/
#include "SphereXSphereJudge.h"

#include <D3DX11.h>
#include "SphereCollider.h"
#include "SphereCSBuffer.h"
#include "CSResult.h"

SphereXSphereJudge::SphereXSphereJudge(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext)
{
	HRESULT hr = NULL;
	//�R���s���[�g�V�F�[�_�[�@�쐬
	SetShaderDirectory();
	ID3DBlob* pErrorBlob = NULL;
	ID3DBlob* pBlob = NULL;
	hr = D3DX11CompileFromFile(L"ComputeSphereXSphere.hlsl", 0, 0, "CS", "cs_5_0",
		0, 0, 0, &pBlob, &pErrorBlob, 0);
	if (FAILED(hr))
	{
		if (pErrorBlob)
		{
			char* sz = NULL;
			sz = (char*)pErrorBlob->GetBufferPointer();
			MessageBoxA(0, sz, 0, MB_OK);
		}
		return;
	}
	pDevice->CreateComputeShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), NULL, &mpSphereXSphereCS);

	mpResult = new CSResult;
	//�R���X�^���g�o�b�t�@�[�쐬�@�����n���p
	D3D11_BUFFER_DESC cb;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.ByteWidth = sizeof(SphereCSBuffer);
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.Usage = D3D11_USAGE_DYNAMIC;
	if (FAILED(pDevice->CreateBuffer(&cb, NULL, &mpSphereInfoBuffer)))
	{
		MessageBoxA(0, "CB FAILED", 0, MB_OK);
	}

	//!���̓o�b�t�@
	ID3D11Buffer* mpBufferInput;
	//�f�[�^�󂯓n���p�̍\���̃o�b�t�@�[�i�X�g���N�`���[�h�o�b�t�@�[�j���`�쐬����
	D3D11_BUFFER_DESC dc;
	ZeroMemory(&dc, sizeof(dc));
	dc.BindFlags = D3D11_BIND_UNORDERED_ACCESS | D3D11_BIND_SHADER_RESOURCE;
	dc.ByteWidth = sizeof(CSResult) * 1;
	dc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
	dc.StructureByteStride = sizeof(CSResult);
	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = mpResult;
	pDevice->CreateBuffer(&dc, &InitData, &mpBufferInput);

	//�f�[�^�󂯎��p�̍\���̃o�b�t�@�[�i�X�g���N�`���[�h�o�b�t�@�[�j���`�쐬����
	ZeroMemory(&dc, sizeof(dc));
	dc.BindFlags = D3D11_BIND_UNORDERED_ACCESS | D3D11_BIND_SHADER_RESOURCE;
	dc.ByteWidth = sizeof(CSResult) * 1;
	dc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
	dc.StructureByteStride = sizeof(CSResult);
	pDevice->CreateBuffer(&dc, NULL, &mpBufferResult);

	//SRV�i�V�F�[�_�[���\�[�X�r���[�j�쐬
	D3D11_SHADER_RESOURCE_VIEW_DESC srd;
	ZeroMemory(&srd, sizeof(srd));
	srd.ViewDimension = D3D11_SRV_DIMENSION_BUFFEREX;
	srd.BufferEx.FirstElement = 0;
	srd.Format = DXGI_FORMAT_UNKNOWN;
	srd.BufferEx.NumElements = 1;
	pDevice->CreateShaderResourceView(mpBufferInput, &srd, &mpBufferInputSRV);

	//UAV �A�N�Z�X�r���[�쐬
	D3D11_UNORDERED_ACCESS_VIEW_DESC ud;
	ZeroMemory(&ud, sizeof(ud));
	ud.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
	ud.Buffer.FirstElement = 0;
	ud.Format = DXGI_FORMAT_UNKNOWN;
	ud.Buffer.NumElements = 1;
	pDevice->CreateUnorderedAccessView(mpBufferResult, &ud, &mpBufferResultUAV);

	SAFE_RELEASE(mpBufferInput);
}

SphereXSphereJudge::~SphereXSphereJudge()
{
	SAFE_RELEASE(mpSphereInfoBuffer);
	SAFE_RELEASE(mpBufferResult);
	SAFE_RELEASE(mpBufferResultUAV);
	SAFE_RELEASE(mpBufferInputSRV);
	SAFE_RELEASE(mpSphereXSphereCS);
	delete mpResult;
}

void SphereXSphereJudge::judge(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext, SphereCollider * sph1, SphereCollider * sph2)
{
	//�R���X�^���g�o�b�t�@�[�ŃV�F�[�_�[��cStart vEnd��n��	
	D3D11_MAPPED_SUBRESOURCE pData;
	if (SUCCEEDED(pDeviceContext->Map(mpSphereInfoBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
	{
		SphereCSBuffer sg;
		sg.sph1 = Vector4(sph1->Position, sph1->Radius);
		sg.sph2 = Vector4(sph2->Position, sph2->Radius);
		memcpy_s(pData.pData, pData.RowPitch, (void*)&sg, sizeof(SphereCSBuffer));
		pDeviceContext->Unmap(mpSphereInfoBuffer, 0);
	}
	pDeviceContext->CSSetConstantBuffers(0, 1, &mpSphereInfoBuffer);
	//�R���s���[�g�V�F�[�_�[���s
	pDeviceContext->CSSetShader(mpSphereXSphereCS, 0, 0);
	pDeviceContext->CSSetShaderResources(0, 1, &mpBufferInputSRV);
	pDeviceContext->CSSetUnorderedAccessViews(0, 1, &mpBufferResultUAV, 0);

	pDeviceContext->Dispatch(1, 1, 1);
	//�R���s���[�g�V�F�[�_�[�̌��ʂ��󂯎��
	ID3D11Buffer* pBufferCopy = NULL;

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	mpBufferResult->GetDesc(&bd);
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
	bd.Usage = D3D11_USAGE_STAGING;
	bd.BindFlags = 0;
	bd.MiscFlags = 0;
	pDevice->CreateBuffer(&bd, NULL, &pBufferCopy);

	pDeviceContext->CopyResource(pBufferCopy, mpBufferResult);

	D3D11_MAPPED_SUBRESOURCE MappedResource;

	pDeviceContext->Map(pBufferCopy, 0, D3D11_MAP_READ, 0, &MappedResource);
	memcpy(mpResult, (CSResult*)MappedResource.pData, sizeof(CSResult));
	pDeviceContext->Unmap(pBufferCopy, 0);
	//����
	float MinLength = FLT_MAX;

	if (mpResult->Hit == 1)
	{
		sph1->result(sph2, true);
		sph2->result(sph1, true);
		SAFE_RELEASE(pBufferCopy);
		return;
	}

	sph1->result(sph2, false);
	sph2->result(sph1, false);
	SAFE_RELEASE(pBufferCopy);
}

/* End of File *****************************************************/