/**
* @file FBXHierarchyMesh.cpp
* @brief FBX階層メッシュクラス実装ファイル
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
	//テクスチャー用サンプラー作成
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
			//メッシュ作成
		case FbxNodeAttribute::eMesh:
			pFBXMesh->createFromFBX(pDevice, pNode->GetMesh());
			break;
		}
	}

	//子がいたら、子で再帰
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
		MessageBox(0, L"FBX初期化失敗", NULL, MB_OK);
		return E_FAIL;
	}

	//読み込み
	FbxNode* pRootNode = mpmyScene->GetRootNode();

	mpRootMesh = new FBXMesh;
	loadRecursive(pDevice, pRootNode, mpRootMesh);

	return S_OK;
}
//
//
//アニメするのはここ。
void FBXHierarchyMesh::recursiveRender(FBXMesh* pMesh, ID3D11DeviceContext* pDeviceContext, ID3D11Buffer* pConstantBuffer, Matrix4x4& world, const Camera* pCamera, const FBXHierarchyMeshRenderDesc* pDesc)
{
	//その瞬間の、自分の姿勢行列を得る
	FbxTime time;
	time.SetTime(0, 0, 0, pDesc->mFrame, 0, FbxTime::eFrames30);//そのフレームに対する時間
	FbxMatrix mCurrentOrientation = pMesh->mpFBXFBXNode->EvaluateGlobalTransform(time / 30);

	//行列コピー　(DirectX ←　FBX)
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			pMesh->mmFBXOrientation(x, y) = (float)mCurrentOrientation.Get(x, y);
		}
	}

	//親の姿勢行列と合成
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