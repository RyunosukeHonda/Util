/**
* @file QuadRenderer.h
* @brief �l�p�`�|���S���`��N���X��`�t�@�C��
* @author Ryunosuke Honda.
*/
#pragma once

#include "ResourceRenderer.h"
#include "ShaderTextureID.h"
#include "Quad.h"
#include "QuadRenderDesc.h"

struct UIQuadRenderDesc;

/**
*	�l�p�`�|���S���`��N���X
*	�P���Ȏl�p�`�|���S���ɔC�ӂ̃V�F�[�_�[��\��t����
*	2DEffect��`�悵�܂�
*	�܂���`�Ɏg�p����V�F�[�_�[���\�[�X��UI�̃C���[�W�ɂ��Ȃ肤�邽��
*	UI�p�̕`��֐��E�L�q�q�f�[�^�z�������
*/
class QuadRenderer : public ResourceRenderer<ShaderTextureID, Quad, QuadRenderDesc>
{
public:
	/**
	 * @fn
	 * �f�t�H���g�R���X�g���N�^
	 */
	QuadRenderer();

	/**
	 * @fn
	 * �f�X�g���N�^
	 */
	~QuadRenderer();

	/**
	* @fn
	* ���b�V���̒ǉ�
	* @brief �t�@�C�����烁�b�V����ǂݍ��݁A�R���e�i�ɒǉ�
	* @param (pDevice) DirectX�`��@��
	* @param (id) ���b�V���Ǘ�ID
	* @param (fileName) �t�@�C����
	* @detail �ǂݍ��݋y�я������̓��b�V���������Ƀ��b�V���N���X�ōs��
	*/
	void addQuad(ID3D11Device* pDevice, const ShaderTextureID & id, const LPCWSTR & fileName);

	/**
	* @fn
	* UI�摜�`��L�q�q�̓o�^
	* @brief �A���t�@�l�ɂ���ēo�^��𕪊򂷂�
	* @param (pDesc) UI�摜�`��L�q�q
	*/
	void registerUIData(const UIQuadRenderDesc* pDesc);

	/**
	* @fn
	* UI�摜�`����s
	* @param (pDeviceContext) DirectX�`��@��
	* @param (UIMatrix) UI���W�n
	*/
	void renderUI(ID3D11DeviceContext* pDeviceContext, const Matrix4x4& UIMatrix);

	/**
	* @fn
	* UI�摜�`��L�q�q�̓o�^
	* @param (pDesc) UI�摜�`��L�q�q
	* @param (UIMatrix) UI���W�n
	*/
	void renderTransparentUI(ID3D11DeviceContext* pDeviceContext, const Matrix4x4& UIMatrix);

	/**
	* @fn
	* �o�^�f�[�^�̃N���A
	*/
	void clearUI();

	// ResourceRenderer ����Čp������܂���
	virtual HRESULT init(ID3D11Device * pDevice) override;
	virtual void render(ID3D11DeviceContext * pDeviceContext, const Camera * pCamera, const DirectionalLightDesc & light) override;
	virtual void renderTransparent(ID3D11DeviceContext * pDeviceContext, const Camera * pCamera, const DirectionalLightDesc & light) override;

private:
	/**
	* @fn
	* �`��ݒ�̏�����
	*/
	void initRenderConfig(ID3D11DeviceContext* pDeviceContext);

	/**
	* @fn
	* �X�v���C�g�̕`����s
	*/
	void renderQuad(const QuadRenderDesc* pDesc, ID3D11DeviceContext* pDeviceContext, const Camera* pCamera, const DirectionalLightDesc& light);

	/**
	* @fn
	* UI�摜�̕`����s
	*/
	void renderUIQuad(const UIQuadRenderDesc* pDesc, ID3D11DeviceContext* pDeviceContext, const Matrix4x4& UIMatrix);

private:
	//!�V�F�[�_�[�ɓn�����o�b�t�@
	ID3D11Buffer* mpConstantBuffer; 
	//!�L�q�q�R���e�i����
	using UIData = std::vector<const UIQuadRenderDesc*>;
	//!�s���߃I�u�W�F�N�g�f�[�^�i�[�R���e�i
	UIData mUIData;
	//!���߃I�u�W�F�N�g�f�[�^�R���e�i
	UIData mTransparentUIData;
};

/* End of File *****************************************************/