/**
* @file Gun.h
* @brief �e�N���X��`�t�@�C��
* @author Ryunosuke Honda.
*/
#pragma once

#include "IShotable.h"
#include "Timer.h"

#include <functional>

class ACharacter;
class ACollider;
class Bullet;

/**
*	�e�N���X
*	�v���C���[�Ɏ������Ďˌ����s��
*/
class Gun : public IShotable
{
public:
	/**
	 * @fn
	 * �R���X�g���N�^�E��ʂ̏e�e�����֐���ێ�
	 */
	Gun(const std::function<void(Bullet*)> generateBulletFunc);

	/**
	 * @fn
	 * �f�X�g���N�^
	 */
	~Gun();

	// IShotable ����Čp������܂���
	virtual void shot(const Transform* parent) override;
	virtual void update() override;

protected:
	//!�A�ˑ��x�E~�b�Ɉꔭ����
	Timer mFireRate;
	//!�e�e�����p�̊֐���ݒ�
	std::function<void(Bullet*)> mGenerateBulletFunc;
};

/* End of File *****************************************************/