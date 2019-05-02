/**
* @file AObject.h
* @brief �I�u�W�F�N�g�C���^�[�t�F�[�X
* @author Ryunosuke Honda.
*/
#pragma once

#include "Base.h"

class IRenderer;

/**
*	�I�u�W�F�N�g�C���^�[�t�F�[�X�E�I�u�W�F�N�g�͍Œ���̋@�\�Ƃ��ĕ`��@�\������
*/
class IObject
{
public:
	/**
	 * @fn
	 * ���z�f�X�g���N�^
	 */
	virtual ~IObject() {}

	/**
	* @fn
	* �`��
	*/
	virtual void draw(IRenderer& renderer) = 0;
};

/* End of File *****************************************************/