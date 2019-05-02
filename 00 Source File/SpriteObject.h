/**
* @file SpriteObject.h
* @brief �X�v���C�g�I�u�W�F�N�g�N���X��`�t�@�C��
* @author Ryunosuke Honda.
*/
#pragma once

#include "IObject.h"
#include "Transform.h"
#include "TextureID.h"
#include "SpriteRenderDesc.h"

/**
*	�X�v���C�g�I�u�W�F�N�g�N���X	
*	�g�����X�t�H�[���A�摜ID�Ȃ�
*	�`��ɕK�v�ȏ����܂Ƃ߂��N���X
*/
class SpriteObject : public Transform, public IObject
{
public:
	/**
	* @fn
	* �R���X�g���N�^
	* @param (id) �摜ID
	*/
	SpriteObject(const TextureID& id);

	/**
	 * @fn
	 * �f�X�g���N�^
	 */
	~SpriteObject();

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

private:
	//!�`��L�q�q
	SpriteRenderDesc mDesc;
};

/* End of File *****************************************************/