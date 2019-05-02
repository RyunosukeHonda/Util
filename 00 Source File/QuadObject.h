/**
* @file QuadObject.h
* @brief ��`�I�u�W�F�N�g�N���X��`�t�@�C��
* @author Ryunosuke Honda.
*/
#pragma once

#include "IObject.h"
#include "Transform.h"
#include "ShaderTextureID.h"
#include "QuadRenderDesc.h"

/**
*	��`�I�u�W�F�N�g�N���X
*	�g�����X�t�H�[���A�V�F�[�_�[ID�Ȃ�
*	�`��ɕK�v�ȏ����܂Ƃ߂��N���X
*/
class QuadObject : public Transform, public IObject
{
public:
	/**
	* @fn
	* �R���X�g���N�^
	* @param (id) �V�F�[�_�[ID
	*/
	QuadObject(const ShaderTextureID& id);
	
	/**
	 * @fn
	 * �f�X�g���N�^
	 */
	~QuadObject();

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
	QuadRenderDesc mDesc;
};

/* End of File *****************************************************/