/**
* @file FBXHierarchyMesh.cpp
* @brief FBX�K�w���b�V���N���X�����t�@�C��
* @author Ryunosuke Honda.
*/
#include "FBXHierarchyMesh.h"
#include "FBXHierarchyMeshRenderDesc.h"

//
//
//
FBXHierarchyMesh::FBXHierarchyMesh(ID3D11Device * pDevice, CHAR* fileName)
{
	loadHierarchyFromFBX(pDevice, fileName);
}
//
//
//
FBXHierarchyMesh::~FBXHierarchyMesh()
{

	if (mpSdkManager) mpSdkManager->Destroy();
	destroyMesh(mpRootMesh);
}

//
//
//
void FBXHierarchyMesh::loadRecursive(ID3D11Device* pDevice, FbxNode* pNode, FBXMesh* pFBXMesh)
{
	//�e�N�X�`���[�p�T���v���[�쐬
	D3D11_SAMPLER_DESC SamDesc;
	ZeroMemory(&SamDesc, sizeof(D3D11_SAMPLER_DESC));

	SamDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	SamDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	pDevice->CreateSamplerState(&SamDesc, &mpSampleLinear);

	//pFBXMesh->mpDevice = mpDevice;
	//pFBXMesh->mpConstantBuffer = mpConstantBuffer;
	//pFBXMesh->mpDeviceContext = mpDeviceContext;
	pFBXMesh->mpSampleLinear = mpSampleLinear;
	pFBXMesh->mpFBXFBXNode = pNode;

	FbxNodeAttribute *pAttr = pNode->GetNodeAttribute();
	if (pAttr != NULL)
	{
		FbxNodeAttribute::EType type = pAttr->GetAttributeType();
		switch (type)
		{
			//���b�V���쐬
		case FbxNodeAttribute::eMesh:
			pFBXMesh->createFromFBX(pDevice, pNode->GetMesh());
			break;
		}
	}

	//�q��������A�q�ōċA
	int iNumChild = pNode->GetChildCount();
	pFBXMesh->mdwNumChild = iNumChild;
	pFBXMesh->mppChild = new FBXMesh*[iNumChild];
	for (int i = 0; i < iNumChild; i++)
	{
		pFBXMesh->mppChild[i] = new FBXMesh;
	}

	for (int i = 0; i < iNumChild; i++)
	{
		FbxNode* ChildNode = pNode->GetChild(i);
		loadRecursive(pDevice, ChildNode, pFBXMesh->mppChild[i]);
	}
}
//
//
//
HRESULT FBXHierarchyMesh::loadHierarchyFromFBX(ID3D11Device* pDevice, CHAR* szFileName)
{
	SetVisualDirectory();
	mpSdkManager = FbxManager::Create();
	mpImporter = FbxImporter::Create(mpSdkManager, "my importer");
	int iFormat = -1;
	mpImporter->Initialize((const char*)szFileName, iFormat);
	mpmyScene = FbxScene::Create(mpSdkManager, "my scene");
	mpImporter->Import(mpmyScene);

	if (mpmyScene == NULL)
	{
		MessageBox(0, L"FBX���������s", NULL, MB_OK);
		return E_FAIL;
	}

	//�ǂݍ���
	FbxNode* pRootNode = mpmyScene->GetRootNode();

	mpRootMesh = new FBXMesh;
	loadRecursive(pDevice, pRootNode, mpRootMesh);

	return S_OK;
}
//
//
//�A�j������̂͂����B
void FBXHierarchyMesh::recursiveRender(FBXMesh* pMesh, ID3D11DeviceContext* pDeviceContext, ID3D11Buffer* pConstantBuffer, Matrix4x4& world, const Camera* pCamera, const FBXHierarchyMeshRenderDesc* pDesc)
{
	//���̏u�Ԃ́A�����̎p���s��𓾂�
	FbxTime time;
	time.SetTime(0, 0, 0, pDesc->mFrame, 0, FbxTime::eFrames30);//���̃t���[���ɑ΂��鎞��
	FbxMatrix mCurrentOrientation = pMesh->mpFBXFBXNode->EvaluateGlobalTransform(time / 30);

	//�s��R�s�[�@(DirectX ���@FBX)
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			pMesh->mmFBXOrientation(x, y) = (float)mCurrentOrientation.Get(x, y);
		}
	}

	//�e�̎p���s��ƍ���
	pMesh->mmParentOrientation = world;
	pMesh->mmFinalWorld = pMesh->mmFBXOrientation * pMesh->mmParentOrientation;
	//RenderMesh(pMesh);
	pMesh->renderMesh(pDeviceContext, pConstantBuffer, world, pCamera, pDesc);

	for (DWORD i = 0; i < pMesh->mdwNumChild; i++)
	{
		recursiveRender(pMesh->mppChild[i], pDeviceContext, pConstantBuffer, world, pCamera, pDesc);
	}
}

//
//
//
void FBXHierarchyMesh::render(ID3D11DeviceContext* pDeviceContext, ID3D11Buffer* pConstantBuffer, const Camera* pCamera, const FBXHierarchyMeshRenderDesc* pDesc)
{
	Matrix4x4 world;
	pDesc->mpTransform->makeWorld(&world);
	recursiveRender(mpRootMesh, pDeviceContext, pConstantBuffer, world, pCamera, pDesc);
}
//
//
//
void FBXHierarchyMesh::destroyMesh(FBXMesh* pMesh)
{
	for (DWORD i = 0; i < pMesh->mdwNumChild; i++)
	{
		if (pMesh->mppChild[i]) destroyMesh(pMesh->mppChild[i]);
	}
	if (pMesh) delete pMesh;
}