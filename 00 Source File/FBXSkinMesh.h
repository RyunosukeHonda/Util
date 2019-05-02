/**
* @file FBXSkinMesh.h
* @brief FBXスキンメッシュクラス定義ファイル
* @author Ryunosuke Honda.
*/
#pragma once
#include "Base.h"
#include <fbxsdk.h>

struct MySkinMaterial;
struct MySkinVertex;
struct Bone;
struct PolyTable;

class Camera;
struct FBXSkinMeshRenderDesc;

//
//class FbxSkinMesh
//FSkinMesh オリジナルメッシュクラス
class FBXSkinMesh : public CElement
{
public:
	//メソッド
	FBXSkinMesh(ID3D11Device* pDevice, CHAR* szFileName);
	~FBXSkinMesh();
	void render(ID3D11DeviceContext* pDeviceContext, ID3D11Buffer* pConstantBuffer, const Camera* pCamera, const FBXSkinMeshRenderDesc* pDesc);
	void setNewPoseMatrices(int frame);
	Matrix4x4 getCurrentPoseMatrix(int index);

private:
	HRESULT initFBX(CHAR* szFileName);
	HRESULT createIndexBuffer(ID3D11Device* pDevice, DWORD dwSize, int* pIndex, ID3D11Buffer** ppIndexBuffer);
	HRESULT createFromFBX(ID3D11Device* pDevice, CHAR* szFileName);
	HRESULT readSkinInfo(FbxMesh* pFbx, MySkinVertex*, PolyTable* PolyTable);

private:
	//FBX
	FbxManager *mpSdkManager;
	FbxImporter* mpImporter;
	FbxScene* mpmyScene;
	//メッシュ関連	
	DWORD mdwNumVert;
	DWORD mdwNumFace;
	DWORD mdwNumUV;
	MySkinMaterial* mpMaterial;
	//ボーン
	PROPERTY_READONLY(DWORD, MaterialCount);
	PROPERTY_READONLY(int, BoneCount);
	Bone* mBoneArray;
	FbxCluster** mppCluster;

	//↓モデルごと	
	ID3D11Buffer** mppIndexBuffer;
	ID3D11Buffer* mpVertexBuffer;
	ID3D11SamplerState* mpSampleLinear;//テクスチャーのサンプラー
	ID3D11ShaderResourceView* mpTexture;//テクスチャー
};