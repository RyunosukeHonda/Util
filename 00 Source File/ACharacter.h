/**
* @file ACharacter.h
* @brief �L�����N�^�[���ۃN���X��`�t�@�C��
* @author Ryunosuke Honda.
*/
#pragma once

#include "IObject.h"
#include "Status.h"

/**
*	���ۃL�����N�^�[�N���X
*/
class ACharacter : public IObject
{
public:
	/**
	* @fn
	* �R���X�g���N�^
	* @param (hp) �̗�
	*/
	ACharacter(int hp);

	/**
	 * @fn
	 * �f�X�g���N�^
	 */
	virtual ~ACharacter() {}

	/**
	* @fn
	* ������
	*/
	virtual void init() = 0;

	/**
	* @fn
	* 60FPS�����X�V
	*/
	virtual void fixedUpdate(float dt) = 0;

	/**
	* @fn
	* ���S���Ă��邩
	*/
	virtual bool isDead() const;

protected:
	//!�X�e�[�^�X
	Status mStatus;
};

/* End of File *****************************************************/