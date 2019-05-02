/**
* @file IShotable.h
* @brief �ˌ��@�\�C���^�[�t�F�[�X
* @author Ryunosuke Honda.
*/
#pragma once

#include "Base.h"

class Transform;

/**
*	�ˌ��@�\�C���^�[�t�F�[�X
*	�v���C���[���e�ۂ����̂Ɏg�p���܂�
*/
class IShotable : public CElement
{
public:
	/**
	 * @fn
	 * ���z�f�X�g���N�^
	 */
	virtual ~IShotable() {}

	/**
	* @fn
	* �ˌ�����
	* @param (������) ������̃g�����X�t�H�[�����
	*/
	virtual void shot(const Transform* parent) = 0;
	
	/**
	* @fn
	* �X�V�����E���[�g�^�C�}�[�̍X�V�ȂǂɎg�p
	*/
	virtual void update() = 0;
};

/* End of File *****************************************************/