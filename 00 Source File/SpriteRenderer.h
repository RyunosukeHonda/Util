/**
* @file SpriteRenderer.h
* @brief �X�v���C�g�Ǘ��N���X��`�t�@�C��
* @author Ryunosuke Honda.
*/
#pragma once

#include "Sprite.h"
#include "TextureID.h"
#include "SpriteRenderDesc.h"
#include "ResourceRenderer.h"

struct UIImageRenderDesc;

/**
*	�X�v���C�g�Ǘ��N���X
*	�X�v���C�g�Ɏg�p���郊�\�[�X��UI�̃C���[�W�ɂ��Ȃ肤�邽��
*	UI�p�̕`��֐��E�L�q�q�f�[�^�z�������
*/
class SpriteRenderer : public ResourceRenderer<TextureID, Sprite, SpriteRenderDesc>
{
public:
	/**
	 * @fn
	 * �f�t�H���g�R���X�g���N�^
	 */
	SpriteRenderer();

	/**
	 * @fn
	 * �f�X�g���N�^
	 */
	~SpriteRenderer();

	/**
	* @fn
	* �X�v���C�g�̒ǉ�
	* @brief �t�@�C������e�N�X�`����ǂݍ��݁A�R���e�i�ɒǉ�
	* @param (pDevice) DirectX�`��@��
	* @param (id) �e�N�X�`���Ǘ�ID
	* @param (fileName) �t�@�C����
	* @detail �ǂݍ��݋y�я������̓X�v���C�g��������Sprite�N���X�ōs��
	*/
	void addSprite(ID3D11Device* pDevice, const TextureID & id, const LPCWSTR & fileName);

	/**
	* @fn
	* UI�摜�`��L�q�q�̓o�^
	* @brief �A���t�@�l�ɂ���ēo�^��𕪊򂷂�
	* @param (pDesc) UI�摜�`��L�q�q
	*/
	void registerUIData(const UIImageRenderDesc* pDesc);

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

	/// ResourceRenderer ����Čp������܂���
	HRESULT init(ID3D11Device* pDevice) override;
	void render(ID3D11DeviceContext* pDeviceContext, const Camera* pCamera, const DirectionalLightDesc& light) override;
	void renderTransparent(ID3D11DeviceContext* pDeviceContext, const Camera* pCamera, const DirectionalLightDesc& light) override;

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
	void renderSprite(const SpriteRenderDesc* pDesc, ID3D11DeviceContext* pDeviceContext, const Camera* pCamera, const DirectionalLightDesc& light);

	/**
	* @fn
	* UI�摜�̕`����s
	*/
	void renderUIImage(const UIImageRenderDesc* pDesc, ID3D11DeviceContext* pDeviceContext, const Matrix4x4& UIMatrix);

private:
	//!���_���C�A�E�g
	ID3D11InputLayout* mpVertexLayout;
	//!�o�[�e�b�N�X�V�F�[�_�[
	ID3D11VertexShader* mpVertexShader;
	//!�s�N�Z���V�F�[�_�[
	ID3D11PixelShader* mpPixelShader;
	//!�V�F�[�_�[�ɓn�����o�b�t�@
	ID3D11Buffer* mpConstantBuffer;

	//!�L�q�q�R���e�i����
	using UIData = std::vector<const UIImageRenderDesc*>;
	//!�s���߃I�u�W�F�N�g�f�[�^�i�[�R���e�i
	UIData mUIData;
	//!���߃I�u�W�F�N�g�f�[�^�R���e�i
	UIData mTransparentUIData;
};

/* End of File *****************************************************/