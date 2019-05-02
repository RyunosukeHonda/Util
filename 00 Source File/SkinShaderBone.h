/**
* @file SkinShaderBone.h
* @brief �X�L�����b�V���̃V�F�[�_�[�p�̃R���X�^���g�o�b�t�@�[�̃A�v�����\����
* @author Ryunosuke Honda.
*/
#pragma once

#include "MathDef.h"

/**
*	�X�L�����b�V���̃V�F�[�_�[�p�̃R���X�^���g�o�b�t�@�[�̃A�v�����\����
*/
struct SkinShaderBone
{
	/**
	* @fn
	* �R���X�g���N�^
	*/
	SkinShaderBone()
	{
		//�s��̏��������s��
		for (int i = 0; i < 256; i++)
		{
			D3DXMatrixIdentity(&mBone[i]);
		}
	}

	//!�{�[���s��z��
	Matrix4x4 mBone[256];
};

/****** End of File *****************************************************/
