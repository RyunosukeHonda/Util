/**
* @file FBXSkinMeshRenderer.h
* @brief FBX�`���̃X�L�����b�V���Ǘ��N���X��`�t�@�C��
* @author Ryunosuke Honda.
*/
#pragma once

#include "FBXSkinMesh.h"
#include "FBXSkinMeshID.h"
#include "FBXSkinMeshRenderDesc.h"
#include "ResourceRenderer.h"

/**
*	FBX�`���̃X�L�����b�V���Ǘ��N���X
*/
class FBXSkinMeshRenderer : public ResourceRenderer<FBXSkinID, FBXSkinMesh, FBXSkinMeshRenderDesc>
{
public:
	/**
	* @fn
	* �R���X�g���N�^
	*/
	FBXSkinMeshRenderer();

	/**
	* @fn
	* �f�X�g���N�^
	*/
	~FBXSkinMeshRenderer();

	/**
	* @fn
	* ���b�V���̒ǉ�
	* @brief �t�@�C�����烁�b�V����ǂݍ��݁A�R���e�i�ɒǉ�
	* @param (pDevice) DirectX�`��@��
	* @param (id) ���b�V���Ǘ�ID
	* @param (fileName) �t�@�C����
	* @detail �ǂݍ��݋y�я������̓��b�V���������Ƀ��b�V���N���X�ōs��
	*/
	void addMesh(ID3D11Device* pDevice, const FBXSkinID & id, const LPSTR & fileName);

	/// ResourceRenderer ����Čp������܂���
	virtual HRESULT init(ID3D11Device* pDevice) override;
	virtual void render(ID3D11DeviceContext* pDeviceContext, const Camera* pCamera, const DirectionalLightDesc & light) override;
	virtual void renderTransparent(ID3D11DeviceContext* pDeviceContext, const Camera* pCamera, const DirectionalLightDesc & light) override;

private:
	using base = ResourceRenderer;

	//�����f���̎�ނ���(���f���̍\�����S�ē���Ȃ�A�v���ɂЂƂj
	ID3D11InputLayout* mpVertexLayout;
	ID3D11VertexShader* mpVertexShader;
	ID3D11PixelShader* mpPixelShader;
	ID3D11Buffer* mpConstantBuffer0;
	ID3D11Buffer* mpConstantBuffer1;
	ID3D11Buffer* mpConstantBuffer2;
};

/* End of File *****************************************************/