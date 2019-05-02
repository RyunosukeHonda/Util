/**
* @file UIQuadObject.h
* @brief UI�p��`�I�u�W�F�N�g�N���X��`�t�@�C��
* @author Ryunosuke Honda.
*/
#pragma once

#include "RectTransform.h"
#include "IObject.h"
#include "ShaderTextureID.h"
#include "UIQuadRenderDesc.h"

/**
*	UI�p��`�I�u�W�F�N�g�N���X
*/
class UIQuadObject : public RectTransform, public IObject
{
public:
	/**
	* @fn
	* �R���X�g���N�^
	* @param (id) �V�F�[�_�[���\�[�XID
	*/
	UIQuadObject(const ShaderTextureID& id);

	/**
	 * @fn
	 * �f�X�g���N�^
	 */
	virtual ~UIQuadObject();

	/**
	* @fn
	*	�F�ݒ�
	* @param (color) �ݒ肷��F
	* @detail
	*	�V�F�[�_�[�ɑ���F��ݒ肷�邾���Ȃ̂�
	*	�Ή����Ă���V�F�[�_�[�̂ݐF���ς��܂�
	*/
	void setColor(Color4& color);

	// IObject ����Čp������܂���
	virtual void draw(IRenderer & renderer) override;

protected:
	//!�`��L�q�q
	UIQuadRenderDesc mDesc;
};

/* End of File *****************************************************/