/**
* @file FBXMesh.h
* @brief FBX(�X�^�e�B�b�N)���b�V���N���X��`�t�@�C��
* @author Ryunosuke Honda.
*/
#pragma once

#include "Base.h"
#include <fbxsdk.h>

struct Fbx_Material;

class Camera;
struct FBXHierarchyMeshRenderDesc;

/**
*	FBX(�X�^�e�B�b�N)���b�V���N���X
*/
class FBXMesh
{
public:
	FBXMesh();
	~FBXMesh();
	HRESULT createFromFBX(ID3D11Device* pDevice, FbxMesh * pFbx);
	void renderMesh(ID3D11DeviceContext* pDeviceContext, ID3D11Buffer* pConstantBuffer, Matrix4x4& world, const Camera* pCamera, const FBXHierarchyMeshRenderDesc* pDesc);

	ID3D11SamplerState* mpSampleLinear;
	FbxNode* mpFBXFBXNode;//FBX����p���s������o���ۂɎg��FBX�|�C���^�[
	DWORD mdwNumChild;//�q�̐�
	FBXMesh** mppChild;//�����̎q�ւ̃|�C���^�[
	//�A�j���[�V�����֘A
	D3DXMATRIX mmParentOrientation;//�e�̎p���s��
	D3DXMATRIX mmFinalWorld;//�ŏI�I�ȃ��[���h�s��i���̎p���Ń����_�����O����j
	D3DXMATRIX mmFBXOrientation;//�����̎p���s��i�e���猩�����Ύp���j
private:
	//FBX
	FbxManager* mpSdkManager;
	FbxImporter* mpImporter;
	FbxScene* mpmyScene;
	//���b�V���֘A	
	DWORD mdwNumVert;
	DWORD mdwNumFace;
	DWORD mdwNumUV;
	ID3D11Buffer* mpVertexBuffer;
	ID3D11Buffer** mppIndexBuffer;
	Fbx_Material* mpMaterial;
	DWORD mdwNumMaterial;

	//���\�b�h
	HRESULT createIndexBuffer(ID3D11Device* pDevice, DWORD dwSize, int* pIndex, ID3D11Buffer** ppIndexBuffer);
};