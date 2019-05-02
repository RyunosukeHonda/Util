/**
* @file FBXMesh.cpp
* @brief FBX(�X�^�e�B�b�N)���b�V���N���X�����t�@�C��
* @author Ryunosuke Honda.
*/
#include "FBXMesh.h"
#include <stdlib.h>
#include <d3dx11.h>
#include "Camera.h"
#include "ShaderWorldColor.h"
#include "Fbx_Material.h"
#include "Fbx_Vertex.h"
#include "FBXHierarchyMeshRenderDesc.h"

//
//
//
FBXMesh::FBXMesh()
{
	ZeroMemory(this, sizeof(FBXMesh));
	D3DXMatrixIdentity(&mmFBXOrientation);
}

//
//
//
FBXMesh::~FBXMesh()
{
	delete[] mpMaterial;
	SAFE_RELEASE(mpVertexBuffer);
	for (DWORD i = 0; i < mdwNumMaterial; i++)
	{
		SAFE_RELEASE(mppIndexBuffer[i]);
	}
	delete[] mppIndexBuffer;
	delete[] mppChild;
}
//
//
//�f�ށiFBX)�̂ق��́A�O�p�|���S���ɂ��邱��
HRESULT FBXMesh::createFromFBX(ID3D11Device* pDevice, FbxMesh* pFbxMesh)
{
	//���O�ɒ��_���A�|���S�������𒲂ׂ�
	mdwNumVert = pFbxMesh->GetControlPointsCount();
	mdwNumUV = pFbxMesh->GetTextureUVCount();
	mdwNumFace = pFbxMesh->GetPolygonCount();
	//�ꎞ�I�ȃ������m�ہi���_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@�j
	Fbx_Vertex* pvVB = NULL;
	mdwNumVert < mdwNumUV ? pvVB = new Fbx_Vertex[mdwNumUV] : pvVB = new Fbx_Vertex[mdwNumVert];
	////�|���S�����ƂɁ@���_�ǂݍ��� �A�@���ǂݍ��݁AUV�ǂݍ���
	FbxVector4 normal;
	for (DWORD i = 0; i < mdwNumFace; i++)
	{
		int iIndex0 = 0;
		int iIndex1 = 0;
		int iIndex2 = 0;

		int iStartIndex = pFbxMesh->GetPolygonVertexIndex(i);
		int* piIndex = pFbxMesh->GetPolygonVertices();//�i���_�C���f�b�N�X�j�ǂݍ���
		iIndex0 = piIndex[iStartIndex];
		iIndex1 = piIndex[iStartIndex + 1];
		iIndex2 = piIndex[iStartIndex + 2];
		if (mdwNumVert < mdwNumUV)//UV���̂ق��������ꍇ�͖{���́i���_�x�[�X�j�C���f�b�N�X�𗘗p���Ȃ��BUV�C���f�b�N�X����ɂ���
		{
			iIndex0 = pFbxMesh->GetTextureUVIndex(i, 0, FbxLayerElement::eTextureDiffuse);
			iIndex1 = pFbxMesh->GetTextureUVIndex(i, 1, FbxLayerElement::eTextureDiffuse);
			iIndex2 = pFbxMesh->GetTextureUVIndex(i, 2, FbxLayerElement::eTextureDiffuse);
		}
		//���_
		int index = pFbxMesh->GetPolygonVertex(i, 0);
		FbxVector4 coord = pFbxMesh->GetControlPointAt(index);
		pvVB[iIndex0].vPos.x = (float)-coord.mData[0];//FBX�͉E����W�n�Ȃ̂�x���邢�͂��𔽓]
		pvVB[iIndex0].vPos.y = (float)coord.mData[1];
		pvVB[iIndex0].vPos.z = (float)coord.mData[2];

		index = pFbxMesh->GetPolygonVertex(i, 1);
		coord = pFbxMesh->GetControlPointAt(index);
		pvVB[iIndex1].vPos.x = (float)-coord.mData[0];//FBX�͉E����W�n�Ȃ̂�x���邢�͂��𔽓]
		pvVB[iIndex1].vPos.y = (float)coord.mData[1];
		pvVB[iIndex1].vPos.z = (float)coord.mData[2];

		index = pFbxMesh->GetPolygonVertex(i, 2);
		coord = pFbxMesh->GetControlPointAt(index);
		pvVB[iIndex2].vPos.x = (float)-coord.mData[0];//FBX�͉E����W�n�Ȃ̂�x���邢�͂��𔽓]
		pvVB[iIndex2].vPos.y = (float)coord.mData[1];
		pvVB[iIndex2].vPos.z = (float)coord.mData[2];
		//�@��		
		pFbxMesh->GetPolygonVertexNormal(i, 0, normal);
		pvVB[iIndex0].vNorm.x = -(float)normal[0];//FBX�͉E����W�n�Ȃ̂�x���邢�͂��𔽓]
		pvVB[iIndex0].vNorm.y = (float)normal[1];
		pvVB[iIndex0].vNorm.z = (float)normal[2];

		pFbxMesh->GetPolygonVertexNormal(i, 1, normal);
		pvVB[iIndex1].vNorm.x = -(float)normal[0];//FBX�͉E����W�n�Ȃ̂�x���邢�͂��𔽓]
		pvVB[iIndex1].vNorm.y = (float)normal[1];
		pvVB[iIndex1].vNorm.z = (float)normal[2];

		pFbxMesh->GetPolygonVertexNormal(i, 2, normal);
		pvVB[iIndex2].vNorm.x = -(float)normal[0];//FBX�͉E����W�n�Ȃ̂�x���邢�͂��𔽓]
		pvVB[iIndex2].vNorm.y = (float)normal[1];
		pvVB[iIndex2].vNorm.z = (float)normal[2];
		//�e�N�X�`���[���W
		int UVindex = pFbxMesh->GetTextureUVIndex(i, 0, FbxLayerElement::eTextureDiffuse);
		FbxLayerElementUV* pUV = 0;

		FbxLayerElementUV* uv = pFbxMesh->GetLayer(0)->GetUVs();

		if (mdwNumUV && uv->GetMappingMode() == FbxLayerElement::eByPolygonVertex)
		{
			//���̎擾�̎d���́AUV�}�b�s���O���[�h��eBY_POLYGON_VERTEX�̎�����Ȃ��Ƃł��Ȃ�
			UVindex = pFbxMesh->GetTextureUVIndex(i, 0, FbxLayerElement::eTextureDiffuse);
			pUV = pFbxMesh->GetLayer(0)->GetUVs();
			FbxVector2 v2 = pUV->GetDirectArray().GetAt(UVindex);
			pvVB[iIndex0].vTex.x = (float)v2.mData[0];
			pvVB[iIndex0].vTex.y = 1.0f - (float)v2.mData[1];

			UVindex = pFbxMesh->GetTextureUVIndex(i, 1, FbxLayerElement::eTextureDiffuse);
			v2 = pUV->GetDirectArray().GetAt(UVindex);
			pvVB[iIndex1].vTex.x = (float)v2.mData[0];
			pvVB[iIndex1].vTex.y = 1.0f - (float)v2.mData[1];

			UVindex = pFbxMesh->GetTextureUVIndex(i, 2, FbxLayerElement::eTextureDiffuse);
			v2 = pUV->GetDirectArray().GetAt(UVindex);
			pvVB[iIndex2].vTex.x = (float)v2.mData[0];
			pvVB[iIndex2].vTex.y = 1.0f - (float)v2.mData[1];
		}
	}

	FbxLayerElementUV* uv = pFbxMesh->GetLayer(0)->GetUVs();
	if (mdwNumUV && uv->GetMappingMode() == FbxLayerElement::eByControlPoint)
	{
		FbxLayerElementUV* pUV = pFbxMesh->GetLayer(0)->GetUVs();
		for (DWORD k = 0; k < mdwNumUV; k++)
		{
			FbxVector2 v2;
			v2 = pUV->GetDirectArray().GetAt(k);
			pvVB[k].vTex.x = (float)v2.mData[0];
			pvVB[k].vTex.y = 1.0f - (float)v2.mData[1];
		}
	}

	//�}�e���A���ǂݍ���
	FbxNode* pNode = pFbxMesh->GetNode();
	mdwNumMaterial = pNode->GetMaterialCount();

	mpMaterial = new Fbx_Material[mdwNumMaterial];

	//�}�e���A���̐������C���f�b�N�X�o�b�t�@�[���쐬
	mppIndexBuffer = new ID3D11Buffer*[mdwNumMaterial];

	for (DWORD i = 0; i < mdwNumMaterial; i++)
	{
		//�t�H�����f����z��
		FbxSurfaceMaterial* pMaterial = pNode->GetMaterial(i);
		FbxSurfacePhong* pPhong = (FbxSurfacePhong*)pMaterial;

		//����
		FbxDouble3 d3Ambient = pPhong->Ambient;
		mpMaterial[i].Ka.x = (float)d3Ambient.mData[0];
		mpMaterial[i].Ka.y = (float)d3Ambient.mData[1];
		mpMaterial[i].Ka.z = (float)d3Ambient.mData[2];
		//�g�U���ˌ�
		FbxDouble3 d3Diffuse = pPhong->Diffuse;
		mpMaterial[i].Kd.x = (float)d3Diffuse.mData[0];
		mpMaterial[i].Kd.y = (float)d3Diffuse.mData[1];
		mpMaterial[i].Kd.z = (float)d3Diffuse.mData[2];
		//���ʔ��ˌ�
		FbxDouble3 d3Specular = pPhong->Specular;
		mpMaterial[i].Ks.x = (float)d3Specular.mData[0];
		mpMaterial[i].Ks.y = (float)d3Specular.mData[1];
		mpMaterial[i].Ks.z = (float)d3Specular.mData[2];
		//�e�N�X�`���[�i�f�B�t���[�Y�e�N�X�`���[�̂݁j
		FbxProperty lProperty;
		lProperty = pMaterial->FindProperty(FbxSurfaceMaterial::sDiffuse);
		FbxTexture* texture = FbxCast<FbxTexture>(lProperty.GetSrcObject(0));
		if (texture)
		{
			strcpy_s(mpMaterial[i].szTextureName, texture->GetName());
			//�e�N�X�`���[���쐬
			if (FAILED(D3DX11CreateShaderResourceViewFromFileA(pDevice, mpMaterial[i].szTextureName, NULL, NULL, &mpMaterial[i].pTexture, NULL)))//��΃p�X�t�@�C�����́A�܂����s����Ǝv�����A�A�A
			{
				char ext[10];
				//_splitpath(mpMaterial[i].szTextureName, 0, 0,mpMaterial[i].szTextureName,ext );
				_splitpath_s(mpMaterial[i].szTextureName, 0, 0, 0, 0, mpMaterial[i].szTextureName, sizeof(mpMaterial[i].szTextureName), ext, sizeof(ext));
				strcat_s(mpMaterial[i].szTextureName, ext);

				if (FAILED(D3DX11CreateShaderResourceViewFromFileA(pDevice, mpMaterial[i].szTextureName, NULL, NULL, &mpMaterial[i].pTexture, NULL)))//�t�@�C�����݂̂Ńg���C
				{
					MessageBox(0, L"�e�N�X�`���[�ǂݍ��ݎ��s", NULL, MB_OK);
					return E_FAIL;
				}
			}
		}
		//�}�e���A���̐������C���f�b�N�X�o�b�t�@�[���쐬
		int iCount = 0;
		int* pIndex = new int[mdwNumFace * 3];//�Ƃ肠�����A���b�V�����̃|���S�����Ń������m�ہi�X�̃|���S���O���[�v�͂��Ȃ炸����ȉ��ɂȂ邪�j

											   //���̃}�e���A���ł���C���f�b�N�X�z����̊J�n�C���f�b�N�X�𒲂ׂ�@����ɃC���f�b�N�X�̌������ׂ�		
		iCount = 0;
		for (DWORD k = 0; k < mdwNumFace; k++)
		{
			FbxLayerElementMaterial* mat = pFbxMesh->GetLayer(0)->GetMaterials();//���C���[��1��������z��
			int matId = mat->GetIndexArray().GetAt(k);
			if (matId == i)
			{
				if (mdwNumVert < mdwNumUV)
				{
					pIndex[iCount] = pFbxMesh->GetTextureUVIndex(k, 0, FbxLayerElement::eTextureDiffuse);
					pIndex[iCount + 1] = pFbxMesh->GetTextureUVIndex(k, 1, FbxLayerElement::eTextureDiffuse);
					pIndex[iCount + 2] = pFbxMesh->GetTextureUVIndex(k, 2, FbxLayerElement::eTextureDiffuse);
				}
				else
				{
					pIndex[iCount] = pFbxMesh->GetPolygonVertex(k, 0);
					pIndex[iCount + 1] = pFbxMesh->GetPolygonVertex(k, 1);
					pIndex[iCount + 2] = pFbxMesh->GetPolygonVertex(k, 2);
				}
				iCount += 3;
			}
		}
		createIndexBuffer(pDevice, iCount * sizeof(int), pIndex, &mppIndexBuffer[i]);
		mpMaterial[i].dwNumFace = iCount / 3;//���̃}�e���A�����̃|���S����

		delete[] pIndex;
	}
	//�o�[�e�b�N�X�o�b�t�@�[���쐬
	if (mdwNumVert < mdwNumUV) mdwNumVert = mdwNumUV;
	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(Fbx_Vertex) *mdwNumVert;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = pvVB;
	if (FAILED(pDevice->CreateBuffer(&bd, &InitData, &mpVertexBuffer)))
		return FALSE;

	//�ꎞ�I�ȓ��ꕨ�́A���͂�s�v
	delete[] pvVB;

	return S_OK;
}

//
//
//
HRESULT FBXMesh::createIndexBuffer(ID3D11Device* pDevice, DWORD dwSize, int* pIndex, ID3D11Buffer** ppIndexBuffer)
{
	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = dwSize;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = pIndex;
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;
	if (FAILED(pDevice->CreateBuffer(&bd, &InitData, ppIndexBuffer)))
	{
		MessageBox(0, L"�o�b�t�@�쐬���s", NULL, MB_OK);
		return FALSE;
	}

	return S_OK;
}
//
//
//
void FBXMesh::renderMesh(ID3D11DeviceContext* pDeviceContext, ID3D11Buffer* pConstantBuffer, Matrix4x4& world, const Camera* pCamera, const FBXHierarchyMeshRenderDesc * pDesc)
{
	//�o�[�e�b�N�X�o�b�t�@�[���Z�b�g�i�o�[�e�b�N�X�o�b�t�@�[�͈�ł����j
	UINT stride = sizeof(Fbx_Vertex);
	UINT offset = 0;
	pDeviceContext->IASetVertexBuffers(0, 1, &mpVertexBuffer, &stride, &offset);

	//�}�e���A���̐������A���ꂼ��̃}�e���A���̃C���f�b�N�X�o�b�t�@�|��`��
	for (DWORD i = 0; i < mdwNumMaterial; i++)
	{
		//�g�p����Ă��Ȃ��}�e���A���΍�
		if (mpMaterial[i].dwNumFace == 0)
		{
			continue;
		}
		//�C���f�b�N�X�o�b�t�@�[���Z�b�g
		stride = sizeof(int);
		offset = 0;
		pDeviceContext->IASetIndexBuffer(mppIndexBuffer[i], DXGI_FORMAT_R32_UINT, 0);

		//�v���~�e�B�u�E�g�|���W�[���Z�b�g
		pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		//�}�e���A���̊e�v�f�ƕϊ��s����V�F�[�_�[�ɓn��

		//���[���h�s����V�F�[�_�[�ɓn��
		//���[���h�E�r���[�E�v���W�F�N�V�����s����V�F�[�_�[�ɓn��
		//�f�B�t���[�Y�J���[���V�F�[�_�[�ɓn��
		//�X�y�L�����[���V�F�[�_�[�ɓn��
		//�X�y�L�����[�̃p���[���V�F�[�_�[�ɓn��
		//�A���r�G���g���V�F�[�_�[�ɓn��
		D3D11_MAPPED_SUBRESOURCE pData;
		if (SUCCEEDED(pDeviceContext->Map(pConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
		{
			ShaderWorldColor sg;
			sg.mW = mmFinalWorld;
			D3DXMatrixTranspose(&sg.mW, &sg.mW);
			sg.mWVP = mmFinalWorld * pCamera->getView() * pCamera->getProj();
			D3DXMatrixTranspose(&sg.mWVP, &sg.mWVP);
			sg.ambient = mpMaterial[i].Ka + pDesc->mAmbient;
			sg.diffuse = mpMaterial[i].Kd + pDesc->mDiffuse;
			sg.specular = mpMaterial[i].Ks + pDesc->mSpecular;
			memcpy_s(pData.pData, pData.RowPitch, (void*)&sg, sizeof(ShaderWorldColor));
			pDeviceContext->Unmap(pConstantBuffer, 0);
		}
		pDeviceContext->VSSetConstantBuffers(1, 1, &pConstantBuffer);
		pDeviceContext->PSSetConstantBuffers(1, 1, &pConstantBuffer);
		//�e�N�X�`���[���V�F�[�_�[�ɓn��
		if (mpMaterial[i].szTextureName[0] != NULL)
		{
			pDeviceContext->PSSetSamplers(0, 1, &mpSampleLinear);
			pDeviceContext->PSSetShaderResources(0, 1, &mpMaterial[i].pTexture);
		}
		//Draw
		pDeviceContext->DrawIndexed(mpMaterial[i].dwNumFace * 3, 0, 0);

	}
}