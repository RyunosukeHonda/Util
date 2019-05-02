/**
* @file UIImageObject.h
* @brief UI�p�摜�I�u�W�F�N�g�N���X��`�t�@�C��
* @author Ryunosuke Honda.
*/
#pragma once

#include "RectTransform.h"
#include "IObject.h"
#include "TextureID.h"
#include "UIImageRenderDesc.h"

/**
*	UI�p�摜�I�u�W�F�N�g�N���X
*/
class UIImageObject : public RectTransform, public IObject
{
public:
	/**
	 * @fn
	 * �R���X�g���N�^
	 */
	UIImageObject(const TextureID& id);

	/**
	 * @fn
	 * �f�X�g���N�^
	 */
	virtual ~UIImageObject();

	/**
	* @fn
	*	�e�N�X�`��ID�ݒ�
	*/
	void setID(const TextureID& id);

	/**
	* @fn
	*	�F�ݒ�
	* @param (color) �ݒ肷��F
	* @detail
	*	�V�F�[�_�[�ɑ���F��ݒ肷�邾���Ȃ̂�
	*	�Ή����Ă���V�F�[�_�[�̂ݐF���ς��܂�
	*/
	void setColor(const Color4& color);

	// IObject ����Čp������܂���
	virtual void draw(IRenderer & renderer) override;

protected:
	//!�`��L�q�q
	UIImageRenderDesc mDesc;
};

/* End of File *****************************************************/