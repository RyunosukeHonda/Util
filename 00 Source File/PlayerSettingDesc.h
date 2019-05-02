/**
* @file PlayerSettingDesc
* @brief �v���C���[�������̐ݒ荀�ڂ��܂Ƃ߂��L�q�q
* @author Ryunosuke Honda.
*/
#pragma once

#include "MathDef.h"
#include "EPlayerIndex.h"

#include <functional>

class Bullet;

/**
*	�v���C���[�������̐ݒ荀�ڂ��܂Ƃ߂��L�q�q
*/
struct PlayerSettingDesc
{
	//!�v���C���[�ԍ�
	EPlayerIndex mIndex;
	//!�̗�
	int mHP;
	//!�����蔻��(���E��)�̃T�C�Y
	float mRadius;
	//!�����ʒu
	Vector3 mPosition;
	//!�e�e�����֐�
	std::function<void(Bullet*)> mGenerateBulletFunc;
};

/****** End of File *****************************************************/
