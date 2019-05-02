/**
* @file FBXSkinMesh.cpp
* @brief FBX�X�L�����b�V���N���X�����t�@�C��
* @author Ryunosuke Honda.
*/
#include "FBXSkinMesh.h"
#include <stdlib.h>
#include <d3dx11.h>
#include "Camera.h"

#include "MySkinMaterial.h"
#include "ShaderWorldColor.h"
#include "MySkinVertex.h"
#include "Bone.h"
#include "PolyTable.h"
#include "FBXSkinMeshRenderDesc.h"

FBXSkinMesh::FBXSkinMesh(ID3D11Device* pDevice, CHAR* fileName)
{
	ZeroMemory(this, sizeof(FBXSkinMesh));
	createFromFBX(pDevice, fileName);
}

FBXSkinMesh::~FBXSkinMesh()
{
	delete[] mBoneArray;
	delete[] mpMaterial;
	delete[] mppCluster;
	SAFE_RELEASE(mpVertexBuffer);
	SAFE_RELEASE(mpSampleLinear);
	for (DWORD i = 0; i < mMaterialCount; i++)
	{
		SAFE_RELEASE(mppIndexBuffer[i]);
	}
	delete[] mppIndexBuffer;
	if (mpSdkManager) mpSdkManager->Destroy();
}

HRESULT FBXSkinMesh::initFBX(CHAR* fileName)
{
	mpSdkManager = FbxManager::Create();

	mpImporter = FbxImporter::Create(mpSdkManager, "my importer");

	int iFormat = -1;
	mpImporter->Initialize((const char*)fileName, iFormat);

	mpmyScene = FbxScene::Create(mpSdkManager, "my scene");

	mpImporter->Import(mpmyScene);

	return S_OK;
}

//
//HRESULT FBXSkinMesh::ReadSkinInfo(FbxMesh* pFbxMesh,MY_SKIN_VERTEX* pvVB,POLY_TABLE* polyTable)
//FBX����X�L���֘A�̏���ǂݏo���@
HRESULT FBXSkinMesh::readSkinInfo(FbxMesh* pFbxMesh, MySkinVertex* pvVB, PolyTable* PolyTable)
{
	//FBX���璊�o���ׂ����́A���_���Ƃ̃{�[���C���f�b�N�X�A���_���Ƃ̃{�[���E�F�C�g�A�o�C���h�s��A�|�[�Y�s��@��4����

	int i, k;
	int iNumBone = 0;//�{�[����

	//�f�t�H�[�}�[�𓾂� 
	FbxDeformer* pDeformer = pFbxMesh->GetDeformer(0);
	FbxSkin* pSkinInfo = static_cast<FbxSkin*>(pDeformer);
	//
	//�{�[���𓾂�
	iNumBone = pSkinInfo->GetClusterCount();
	mppCluster = new  FbxCluster*[iNumBone];
	for (i = 0; i < iNumBone; i++)
	{
		mppCluster[i] = pSkinInfo->GetCluster(i);
	}

	//�ʏ�̏ꍇ�@�i���_����=UV���@pvVB�����_�C���f�b�N�X�x�[�X�̏ꍇ�j
	if (mdwNumVert >= mdwNumUV)
	{
		//���ꂼ��̃{�[���ɉe�����󂯂钸�_�𒲂ׂ�@��������t�ɁA���_�x�[�X�Ń{�[���C���f�b�N�X�E�d�݂𐮓ڂ���
		for (i = 0; i < iNumBone; i++)
		{
			int iNumIndex = mppCluster[i]->GetControlPointIndicesCount();//���̃{�[���ɉe�����󂯂钸�_��
			int* piIndex = mppCluster[i]->GetControlPointIndices();
			double* pdWeight = mppCluster[i]->GetControlPointWeights();
			//���_������C���f�b�N�X�����ǂ��āA���_�T�C�h�Ő�������
			for (k = 0; k < iNumIndex; k++)
			{
				for (int m = 0; m < 4; m++)//FBX��CG�\�t�g���{�[��4�{�ȓ��Ƃ͌���Ȃ��B5�{�ȏ�̏ꍇ�́A�d�݂̑傫������4�{�ɍi�� 
				{
					if (pdWeight[k] > pvVB[piIndex[k]].bBoneWeight[m])
					{
						pvVB[piIndex[k]].bBoneIndex[m] = i;
						pvVB[piIndex[k]].bBoneWeight[m] = pdWeight[k];
						break;
					}
				}
			}
		}
	}
	//UV�C���f�b�N�X�x�[�X�̏ꍇ�@�i���_��<UV���j
	else
	{
		int PolyIndex = 0;
		int UVIndex = 0;
		//���ꂼ��̃{�[���ɉe�����󂯂钸�_�𒲂ׂ�@��������t�ɁA���_�x�[�X�Ń{�[���C���f�b�N�X�E�d�݂𐮓ڂ���
		for (i = 0; i < iNumBone; i++)
		{
			int iNumIndex = mppCluster[i]->GetControlPointIndicesCount();//���̃{�[���ɉe�����󂯂钸�_��
			int* piIndex = mppCluster[i]->GetControlPointIndices();
			double* pdWeight = mppCluster[i]->GetControlPointWeights();
			//���_������C���f�b�N�X�����ǂ��āA���_�T�C�h�Ő�������
			for (k = 0; k < iNumIndex; k++)
			{
				//���̒��_���܂�ł���|���S�����ׂĂɁA���̃{�[���ƃE�F�C�g��K�p
				for (int p = 0; p < PolyTable[piIndex[k]].NumRef; p++)
				{
					//���_�������|���S�������̃|���S����UV�C���f�b�N�X�@�Ƌt����
					PolyIndex = PolyTable[piIndex[k]].PolyIndex[p];
					UVIndex = pFbxMesh->GetTextureUVIndex(PolyIndex, PolyTable[piIndex[k]].Index123[p], FbxLayerElement::eTextureDiffuse);

					for (int m = 0; m < 4; m++)//FBX��CG�\�t�g���{�[��4�{�ȓ��Ƃ͌���Ȃ��B5�{�ȏ�̏ꍇ�́A�d�݂̑傫������4�{�ɍi�� 
					{
						if (pdWeight[k] > pvVB[UVIndex].bBoneWeight[m])
						{
							pvVB[UVIndex].bBoneIndex[m] = i;
							pvVB[UVIndex].bBoneWeight[m] = pdWeight[k];
							break;
						}
					}
				}

			}
		}
	}

	//
	//�{�[���𐶐�
	mBoneCount = iNumBone;
	mBoneArray = new Bone[iNumBone];

	for (i = 0; i < mBoneCount; i++)
	{
		FbxAMatrix mat;
		mppCluster[i]->GetTransformLinkMatrix(mat);

		for (int x = 0; x < 4; x++)
		{
			for (int y = 0; y < 4; y++)
			{
				mBoneArray[i].mBindPose(y, x) = mat.Get(y, x);
				mBoneArray[i].mBindPose._11 *= -1;
			}
		}
	}
	return S_OK;
}

HRESULT FBXSkinMesh::createFromFBX(ID3D11Device* pDevice, CHAR* fileName)
{
	//FBX���[�_�[��������
	SetVisualDirectory();
	if (FAILED(initFBX(fileName)))
	{
		MessageBox(0, L"FBX���[�_�[���������s", NULL, MB_OK);
		return E_FAIL;
	}

	FbxNode* pNode = mpmyScene->GetRootNode();

	int index = 0;
	FbxNodeAttribute* pAttr = pNode->GetNodeAttribute();
	while (!pAttr || pAttr->GetAttributeType() != FbxNodeAttribute::eMesh)//1���b�V����z�肵�Ă���̂ŁAeMesh�������������_�ŁA������g��
	{
		pNode = pNode->GetChild(index);
		index++;
		pAttr = pNode->GetNodeAttribute();
	}

	FbxMesh* pFbxMesh = pNode->GetMesh();

	//���O�ɒ��_���A�|���S�������𒲂ׂ�
	mdwNumVert = pFbxMesh->GetControlPointsCount();
	mdwNumUV = pFbxMesh->GetTextureUVCount();
	mdwNumFace = pFbxMesh->GetPolygonCount();
	//�ꎞ�I�ȃ������m�ہi���_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@�j
	MySkinVertex* pvVB = NULL;
	mdwNumVert < mdwNumUV ? pvVB = new MySkinVertex[mdwNumUV] : pvVB = new MySkinVertex[mdwNumVert];
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
		pvVB[iIndex0].vPos.x = (float)-coord.mData[0];
		pvVB[iIndex0].vPos.y = (float)coord.mData[1];
		pvVB[iIndex0].vPos.z = (float)coord.mData[2];

		index = pFbxMesh->GetPolygonVertex(i, 1);
		coord = pFbxMesh->GetControlPointAt(index);
		pvVB[iIndex1].vPos.x = (float)-coord.mData[0];
		pvVB[iIndex1].vPos.y = (float)coord.mData[1];
		pvVB[iIndex1].vPos.z = (float)coord.mData[2];

		index = pFbxMesh->GetPolygonVertex(i, 2);
		coord = pFbxMesh->GetControlPointAt(index);
		pvVB[iIndex2].vPos.x = (float)-coord.mData[0];
		pvVB[iIndex2].vPos.y = (float)coord.mData[1];
		pvVB[iIndex2].vPos.z = (float)coord.mData[2];
		//�@��
		pFbxMesh->GetPolygonVertexNormal(i, 0, normal);
		pvVB[iIndex0].vNorm.x = -(float)normal[0];
		pvVB[iIndex0].vNorm.y = (float)normal[1];
		pvVB[iIndex0].vNorm.z = (float)normal[2];

		pFbxMesh->GetPolygonVertexNormal(i, 1, normal);
		pvVB[iIndex1].vNorm.x = -(float)normal[0];
		pvVB[iIndex1].vNorm.y = (float)normal[1];
		pvVB[iIndex1].vNorm.z = (float)normal[2];

		pFbxMesh->GetPolygonVertexNormal(i, 2, normal);
		pvVB[iIndex2].vNorm.x = -(float)normal[0];
		pvVB[iIndex2].vNorm.y = (float)normal[1];
		pvVB[iIndex2].vNorm.z = (float)normal[2];
		//�e�N�X�`���[���W
		int UVindex = pFbxMesh->GetTextureUVIndex(i, 0, FbxLayerElement::eTextureDiffuse);
		FbxLayerElementUV* pUV = 0;

		FbxLayerElementUV* uv = pFbxMesh->GetLayer(0)->GetUVs();

		if (mdwNumUV && uv->GetMappingMode() == FbxLayerElement::eByPolygonVertex)
		{
			//���̎擾�̎d���́AUV�}�b�s���O���[�h��eByPolygonVertex�̎�����Ȃ��Ƃł��Ȃ�
			UVindex = pFbxMesh->GetTextureUVIndex(i, 0, FbxLayerElement::eTextureDiffuse);
			pUV = pFbxMesh->GetLayer(0)->GetUVs();
			FbxVector2 v2 = pUV->GetDirectArray().GetAt(UVindex);
			pvVB[iIndex0].vTex.x = v2.mData[0];
			pvVB[iIndex0].vTex.y = 1.0f - v2.mData[1];

			UVindex = pFbxMesh->GetTextureUVIndex(i, 1, FbxLayerElement::eTextureDiffuse);
			v2 = pUV->GetDirectArray().GetAt(UVindex);
			pvVB[iIndex1].vTex.x = v2.mData[0];
			pvVB[iIndex1].vTex.y = 1.0f - v2.mData[1];

			UVindex = pFbxMesh->GetTextureUVIndex(i, 2, FbxLayerElement::eTextureDiffuse);
			v2 = pUV->GetDirectArray().GetAt(UVindex);
			pvVB[iIndex2].vTex.x = v2.mData[0];
			pvVB[iIndex2].vTex.y = 1.0f - v2.mData[1];
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
			pvVB[k].vTex.x = v2.mData[0];
			pvVB[k].vTex.y = 1.0f - v2.mData[1];
		}
	}

	//�}�e���A���ǂݍ���
	pNode = pFbxMesh->GetNode();
	mMaterialCount = pNode->GetMaterialCount();

	mpMaterial = new MySkinMaterial[mMaterialCount];

	//�}�e���A���̐������C���f�b�N�X�o�b�t�@�[���쐬
	mppIndexBuffer = new ID3D11Buffer*[mMaterialCount];

	for (DWORD i = 0; i < mMaterialCount; i++)
	{
		//�t�H�����f����z��
		FbxSurfaceMaterial* pMaterial = pNode->GetMaterial(i);
		FbxSurfacePhong* pPhong = (FbxSurfacePhong*)pMaterial;

		//����
		FbxDouble3 d3Ambient = pPhong->Ambient;
		mpMaterial[i].Ka.r = (float)d3Ambient.mData[0];
		mpMaterial[i].Ka.g = (float)d3Ambient.mData[1];
		mpMaterial[i].Ka.b = (float)d3Ambient.mData[2];
		mpMaterial[i].Ka.a = 1;
		//�g�U���ˌ�
		FbxDouble3 d3Diffuse = pPhong->Diffuse;
		mpMaterial[i].Kd.r = (float)d3Diffuse.mData[0];
		mpMaterial[i].Kd.g = (float)d3Diffuse.mData[1];
		mpMaterial[i].Kd.b = (float)d3Diffuse.mData[2];
		mpMaterial[i].Kd.a = 1;
		//���ʔ��ˌ�
		FbxDouble3 d3Specular = pPhong->Diffuse;
		mpMaterial[i].Ks.r = (float)d3Specular.mData[0];
		mpMaterial[i].Ks.g = (float)d3Specular.mData[1];
		mpMaterial[i].Ks.b = (float)d3Specular.mData[2];
		mpMaterial[i].Ks.a = 1;
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
				_splitpath(mpMaterial[i].szTextureName, 0, 0, mpMaterial[i].szTextureName, ext);
				//_splitpath_s(mpMaterial[i].szTextureName, 0, 0,0,0,mpMaterial[i].szTextureName,sizeof(mpMaterial[i].szTextureName),ext,sizeof(ext) );
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
		if (iCount > 0) createIndexBuffer(pDevice, iCount * sizeof(int), pIndex, &mppIndexBuffer[i]);
		mpMaterial[i].dwNumFace = iCount / 3;//���̃}�e���A�����̃|���S����		
		delete[] pIndex;
	}

	//���_����|���S�����t�����������̂ŁA�t�����e�[�u������� 
	PolyTable* polyTable = new PolyTable[mdwNumVert];

	for (DWORD i = 0; i < mdwNumVert; i++)
	{
		for (DWORD k = 0; k < mdwNumFace; k++)
		{
			for (int m = 0; m < 3; m++)
			{
				if (pFbxMesh->GetPolygonVertex(k, m) == i)
				{
					polyTable[i].PolyIndex[polyTable[i].NumRef] = k;
					polyTable[i].Index123[polyTable[i].NumRef] = m;
					polyTable[i].NumRef++;
				}
			}
		}
	}

	//�X�L�����i�W���C���g�A�E�F�C�g�@�j�ǂݍ���
	readSkinInfo(pFbxMesh, pvVB, polyTable);

	//�o�[�e�b�N�X�o�b�t�@�[���쐬
	if (mdwNumVert < mdwNumUV) mdwNumVert = mdwNumUV;
	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(MySkinVertex) *mdwNumVert;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = pvVB;
	if (FAILED(pDevice->CreateBuffer(&bd, &InitData, &mpVertexBuffer)))
		return FALSE;

	//�ꎞ�I�ȓ��ꕨ�́A���͂�s�v
	delete[] pvVB;

	//�e�N�X�`���[�p�T���v���[�쐬
	D3D11_SAMPLER_DESC SamDesc;
	ZeroMemory(&SamDesc, sizeof(D3D11_SAMPLER_DESC));

	SamDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	SamDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	pDevice->CreateSamplerState(&SamDesc, &mpSampleLinear);

	return S_OK;
}

HRESULT FBXSkinMesh::createIndexBuffer(ID3D11Device* pDevice, DWORD dwSize, int* pIndex, ID3D11Buffer** ppIndexBuffer)
{
	//Direct3D11& d3D = singleton<Direct3D11>::get_instance();
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
		return FALSE;
	}

	return S_OK;
}
//
//void FBXSkinMesh::SetNewPoseMatrices(int frame)
//�{�[�������̃|�[�Y�ʒu�ɃZ�b�g����
void FBXSkinMesh::setNewPoseMatrices(int frame)
{
	Matrix4x4 m(-1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);
	int i;
	FbxTime time;
	time.SetTime(0, 0, 0, frame, 0, FbxTime::eFrames30);//30�t���[��/�b�@�Ɛ���@�����ɂ͏󋵂��Ƃɒ��ׂ�K�v����

	for (i = 0; i < mBoneCount; i++)
	{
		FbxMatrix mat = mppCluster[i]->GetLink()->EvaluateGlobalTransform(time);

		for (int x = 0; x < 4; x++)
		{
			for (int y = 0; y < 4; y++)
			{
				mBoneArray[i].mNewPose(y, x) = mat.Get(y, x);
			}
		}
		mBoneArray[i].mNewPose *= m;//FBX�E����W�n�Ȃ̂ł����t�@�␳����
	}
}
//
//Matrix4x4 FBXSkinMesh::GetCurrentPoseMatrix(int index)
//���́i���݂́j�|�[�Y�s���Ԃ�
Matrix4x4 FBXSkinMesh::getCurrentPoseMatrix(int index)
{
	Matrix4x4 inv;
	D3DXMatrixInverse(&inv, 0, &mBoneArray[index].mBindPose);//FBX�̃o�C���h�|�[�Y�͏����p���i��΍��W�j
	Matrix4x4 ret = inv*mBoneArray[index].mNewPose;//�o�C���h�|�[�Y�̋t�s��ƃt���[���p���s���������B�Ȃ��A�o�C���h�|�[�Y���̂����ɋt�s��ł���Ƃ���l��������B�iFBX�̏ꍇ�͈Ⴄ���j

	return ret;
}

void FBXSkinMesh::render(ID3D11DeviceContext* pDeviceContext, ID3D11Buffer* pConstantBuffer, const Camera* pCamera, const FBXSkinMeshRenderDesc* pDesc)
{
	//�o�[�e�b�N�X�o�b�t�@�[���Z�b�g�i�o�[�e�b�N�X�o�b�t�@�[�͈�ł����j
	UINT stride = sizeof(MySkinVertex);
	UINT offset = 0;
	pDeviceContext->IASetVertexBuffers(0, 1, &mpVertexBuffer, &stride, &offset);

	//�}�e���A���̐������A���ꂼ��̃}�e���A���̃C���f�b�N�X�o�b�t�@�|��`��
	for (DWORD i = 0; i < mMaterialCount; i++)
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
		Matrix4x4 world;
		pDesc->mpTransform->makeWorld(&world);
		//���[���h�E�r���[�E�v���W�F�N�V�����s����V�F�[�_�[�ɓn��
		//�f�B�t���[�Y�J���[���V�F�[�_�[�ɓn��
		//�X�y�L�����[���V�F�[�_�[�ɓn��
		//�X�y�L�����[�̃p���[���V�F�[�_�[�ɓn��
		//�A���r�G���g���V�F�[�_�[�ɓn��
		D3D11_MAPPED_SUBRESOURCE pData;
		if (SUCCEEDED(pDeviceContext->Map(pConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
		{
			ShaderWorldColor sg;
			sg.mW = world;
			D3DXMatrixTranspose(&sg.mW, &sg.mW);
			sg.mWVP = world * pCamera->getView() * pCamera->getProj();
			D3DXMatrixTranspose(&sg.mWVP, &sg.mWVP);
			sg.ambient = mpMaterial[i].Ka + pDesc->mAmbient;
			sg.diffuse = mpMaterial[i].Kd + pDesc->mDiffuse;
			sg.diffuse.a = pDesc->mDiffuse.a;
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