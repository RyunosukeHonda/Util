/**
* @file FBXHierarchyMesh.h
* @brief FBX階層メッシュクラス定義ファイル
* @author Ryunosuke Honda.
*/
#pragma once
#include "FBXMesh.h"

//#pragma comment(lib,"fbxsdk_20113d.lib")
#pragma comment(lib,"libfbxsdk-mt.lib")
#pragma comment(lib,"wininet.lib")

struct FBXHierarchyMeshRenderDesc;

/**
*	FBX階層メッシュクラス
*/
class FBXHierarchyMesh
{
public:
	FBXHierarchyMesh(ID3D11Device * pDevice, CHAR* fileName);
	~FBXHierarchyMesh();
	void render(ID3D11DeviceContext* pDeviceContext, ID3D11Buffer* pConstantBuffer, const Camera* pCamera, const FBXHierarchyMeshRenderDesc* pDesc);

private:
	HRESULT loadHierarchyFromFBX(ID3D11Device* pDevice, CHAR* szFileName);
	void loadRecursive(ID3D11Device* pDevice, FbxNode* pNode, FBXMesh* pFBXMesh);
	void recursiveRender(FBXMesh* pMesh, ID3D11DeviceContext* pDeviceContext, ID3D11Buffer* pConstantBuffer, Matrix4x4& world, const Camera* pCamera, const FBXHierarchyMeshRenderDesc* pDesc);
	void destroyMesh(FBXMesh* pMesh);
	
private:
	//FBX
	FBXMesh* mpRootMesh;
	FbxManager *mpSdkManager;
	FbxImporter* mpImporter;
	FbxScene* mpmyScene;
	ID3D11SamplerState* mpSampleLinear;
	ID3D11Buffer* mpConstantBuffer;
};

/****** End of File *****************************************************/