/**
* @file FBXMesh.h
* @brief FBX(スタティック)メッシュクラス定義ファイル
* @author Ryunosuke Honda.
*/
#pragma once

#include "Base.h"
#include <fbxsdk.h>

struct Fbx_Material;

class Camera;
struct FBXHierarchyMeshRenderDesc;

/**
*	FBX(スタティック)メッシュクラス
*/
class FBXMesh
{
public:
	FBXMesh();
	~FBXMesh();
	HRESULT createFromFBX(ID3D11Device* pDevice, FbxMesh * pFbx);
	void renderMesh(ID3D11DeviceContext* pDeviceContext, ID3D11Buffer* pConstantBuffer, Matrix4x4& world, const Camera* pCamera, const FBXHierarchyMeshRenderDesc* pDesc);

	ID3D11SamplerState* mpSampleLinear;
	FbxNode* mpFBXFBXNode;//FBXから姿勢行列を取り出す際に使うFBXポインター
	DWORD mdwNumChild;//子の数
	FBXMesh** mppChild;//自分の子へのポインター
	//アニメーション関連
	D3DXMATRIX mmParentOrientation;//親の姿勢行列
	D3DXMATRIX mmFinalWorld;//最終的なワールド行列（この姿勢でレンダリングする）
	D3DXMATRIX mmFBXOrientation;//自分の姿勢行列（親から見た相対姿勢）
private:
	//FBX
	FbxManager* mpSdkManager;
	FbxImporter* mpImporter;
	FbxScene* mpmyScene;
	//メッシュ関連	
	DWORD mdwNumVert;
	DWORD mdwNumFace;
	DWORD mdwNumUV;
	ID3D11Buffer* mpVertexBuffer;
	ID3D11Buffer** mppIndexBuffer;
	Fbx_Material* mpMaterial;
	DWORD mdwNumMaterial;

	//メソッド
	HRESULT createIndexBuffer(ID3D11Device* pDevice, DWORD dwSize, int* pIndex, ID3D11Buffer** ppIndexBuffer);
};