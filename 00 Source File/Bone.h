/**
* @file Bone.h
* @brief �{�[���\����
* @author Ryunosuke Honda.
*/
#pragma once

#include "Base.h"

/**
*	�{�[���\����
*/
struct Bone
{
	//!�����|�[�Y�i�����ƕς��Ȃ��j
	Matrix4x4 mBindPose;
	//!���݂̃|�[�Y�i���̓s�x�ς��j
	Matrix4x4 mNewPose;
	
	/**
	* @fn
	* �R���X�g���N�^
	*/
	Bone()
	{
		ZeroMemory(this, sizeof(Bone));
	}
};

/****** End of File *****************************************************/
