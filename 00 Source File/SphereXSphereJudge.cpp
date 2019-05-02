/**
* @file SphereXSphereJudge.cpp
* @brief 境界球同士の衝突判定クラス実装ファイル
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
	//コンピュートシェーダー　作成
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
	//コンスタントバッファー作成　球情報渡し用
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

	//!入力バッファ
	ID3D11Buffer* mpBufferInput;
	//データ受け渡し用の構造体バッファー（ストラクチャードバッファー）を定義作成する
	D3D11_BUFFER_DESC dc;
	ZeroMemory(&dc, sizeof(dc));
	dc.BindFlags = D3D11_BIND_UNORDERED_ACCESS | D3D11_BIND_SHADER_RESOURCE;
	dc.ByteWidth = sizeof(CSResult) * 1;
	dc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
	dc.StructureByteStride = sizeof(CSResult);
	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = mpResult;
	pDevice->CreateBuffer(&dc, &InitData, &mpBufferInput);

	//データ受け取り用の構造体バッファー（ストラクチャードバッファー）を定義作成する
	ZeroMemory(&dc, sizeof(dc));
	dc.BindFlags = D3D11_BIND_UNORDERED_ACCESS | D3D11_BIND_SHADER_RESOURCE;
	dc.ByteWidth = sizeof(CSResult) * 1;
	dc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
	dc.StructureByteStride = sizeof(CSResult);
	pDevice->CreateBuffer(&dc, NULL, &mpBufferResult);

	//SRV（シェーダーリソースビュー）作成
	D3D11_SHADER_RESOURCE_VIEW_DESC srd;
	ZeroMemory(&srd, sizeof(srd));
	srd.ViewDimension = D3D11_SRV_DIMENSION_BUFFEREX;
	srd.BufferEx.FirstElement = 0;
	srd.Format = DXGI_FORMAT_UNKNOWN;
	srd.BufferEx.NumElements = 1;
	pDevice->CreateShaderResourceView(mpBufferInput, &srd, &mpBufferInputSRV);

	//UAV アクセスビュー作成
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
	//コンスタントバッファーでシェーダーにcStart vEndを渡す	
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
	//コンピュートシェーダー実行
	pDeviceContext->CSSetShader(mpSphereXSphereCS, 0, 0);
	pDeviceContext->CSSetShaderResources(0, 1, &mpBufferInputSRV);
	pDeviceContext->CSSetUnorderedAccessViews(0, 1, &mpBufferResultUAV, 0);

	pDeviceContext->Dispatch(1, 1, 1);
	//コンピュートシェーダーの結果を受け取る
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
	//結果
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