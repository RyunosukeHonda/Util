/**
* @file OBJStaticMeshRenderer.h
* @brief OBJ�`���̃X�^�e�B�b�N���b�V���`��N���X��`�t�@�C��
* @author Ryunosuke Honda.
*/
#pragma once

#include "Direct3D11.h"
#include "OBJStaticMeshID.h"
#include "OBJStaticMesh.h"
#include "OBJStaticMeshRenderDesc.h"
#include "ResourceRenderer.h"

/**
*	OBJ�`���̃X�^�e�B�b�N���b�V���`��N���X
*/
class OBJStaticMeshRenderer : public ResourceRenderer<OBJMeshID, OBJStaticMesh, OBJStaticMeshRenderDesc>
{
public:
	/**
	 * @fn
	 * �R���X�g���N�^
	 */
	OBJStaticMeshRenderer();
	
	/**
	 * @fn
	 * �f�X�g���N�^
	 */
	~OBJStaticMeshRenderer();

	/**
	* @fn
	* ���b�V���̒ǉ�
	* @brief �t�@�C�����烁�b�V����ǂݍ��݁A�R���e�i�ɒǉ�
	* @param (pDevice) DirectX�`��@��
	* @param (id) ���b�V���Ǘ�ID
	* @param (fileName) �t�@�C����
	* @detail �ǂݍ��݋y�я������̓��b�V���������Ƀ��b�V���N���X�ōs��
	*/
	void addMesh(ID3D11Device* pDevice, const OBJMeshID & id, const LPSTR & fileName);

	/// ResourceRenderer ����Čp������܂���
	virtual HRESULT init(ID3D11Device* pDevice) override;
	virtual void render(ID3D11DeviceContext * pDeviceContext, const Camera * pCamera, const DirectionalLightDesc & light) override;
	virtual void renderTransparent(ID3D11DeviceContext * pDeviceContext, const Camera * pCamera, const DirectionalLightDesc & light) override;

private:
	//!���N���X����
	using base = ResourceRenderer;
	//!���_�V�F�[�_�[
	ID3D11VertexShader* mpVertexShader;
	//!���_���C�A�E�g
	ID3D11InputLayout* mpVertexLayout;
	//!�s�N�Z���V�F�[�_�[
	ID3D11PixelShader* mpPixelShader;
	//!�萔�o�b�t�@�E�`��ʒu���p
	ID3D11Buffer* mpConstantBuffer0;
	//!�萔�o�b�t�@�E�F���p
	ID3D11Buffer* mpConstantBuffer1;
};

/* End of File *****************************************************/