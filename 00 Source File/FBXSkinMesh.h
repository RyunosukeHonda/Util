/**
* @file FBXSkinMesh.h
* @brief FBX�X�L�����b�V���N���X��`�t�@�C��
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
//FSkinMesh �I���W�i�����b�V���N���X
class FBXSkinMesh : public CElement
{
public:
	//���\�b�h
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
	//���b�V���֘A	
	DWORD mdwNumVert;
	DWORD mdwNumFace;
	DWORD mdwNumUV;
	MySkinMaterial* mpMaterial;
	//�{�[��
	PROPERTY_READONLY(DWORD, MaterialCount);
	PROPERTY_READONLY(int, BoneCount);
	Bone* mBoneArray;
	FbxCluster** mppCluster;

	//�����f������	
	ID3D11Buffer** mppIndexBuffer;
	ID3D11Buffer* mpVertexBuffer;
	ID3D11SamplerState* mpSampleLinear;//�e�N�X�`���[�̃T���v���[
	ID3D11ShaderResourceView* mpTexture;//�e�N�X�`���[
};