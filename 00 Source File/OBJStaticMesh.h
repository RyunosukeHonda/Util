/**
* @file OBJStaticMesh.h
* @brief OBJ�`���̃X�^�e�B�b�N���b�V���N���X��`�t�@�C��
* @author Ryunosuke Honda.
*/
#pragma once

#include "Base.h"

class Camera;

struct MyMaterial;
struct MyVertex;
struct OBJStaticMeshRenderDesc;

/**
*	OBJ�`���̃X�^�e�B�b�N���b�V���N���X
*/
class OBJStaticMesh : public CElement
{
public:
	/**
	* @fn
	* �R���X�g���N�^
	* @param (pDevice) �`��f�o�C�X
	* @param (fileName) �ǂݍ��ރt�@�C����
	*/
	OBJStaticMesh(ID3D11Device* pDevice, LPSTR fileName);

	/**
	* @fn
	* �f�X�g���N�^
	*/
	~OBJStaticMesh();

	void render(ID3D11DeviceContext* pDeviceContext, ID3D11Buffer* mpConstantBuffer1, const OBJStaticMeshRenderDesc* pDesc);

private:
	/**
	* @fn
	* ���b�V��������
	* @return ����ɏI��������
	*/
	HRESULT InitStaticMesh(ID3D11Device* pDevice, LPSTR FileName);

	/**
	* @fn
	* �t�@�C������}�e���A����ǂݍ���
	* @return ����ɏI��������
	*/
	HRESULT LoadMaterialFromFile(ID3D11Device* pDevice, LPSTR FileName, MyMaterial** ppMaterial, DWORD* pdwNUmMaterial);

private:
	//!�}�e���A�����̖ʂ̐�
	DWORD* mdwNumFaceInMaterial;
	//! �o�[�e�b�N�X�o�b�t�@�[
	ID3D11Buffer* mpVertexBuffer;
	//! �C���f�b�N�X�o�b�t�@�[
	ID3D11Buffer** mppIndexBuffer;
	int** mppiVertexIndex;
	//! �}�e���A����
	DWORD mdwNumMaterial;
	//! �g�p�}�e���A��(�z��)
	MyMaterial* mpMaterial;
	//!���_�\����
	MyVertex* mpvVertexBuffer;
	//!�T���v�����j�A
	ID3D11SamplerState* mpSampleLinear;
};

/****** End of File *****************************************************/
