/**
* @file ColorConstantBuffer.h
* @brief �V�F�[�_�[�ɑ���J���[���\����
* @author Ryunosuke Honda.
*/
#pragma once

#include "MathDef.h"

/**
*	�J���[���\����
*/
struct ColorConstantBuffer
{
	//!�A���r�G���g��
	Color4 ambient;
	//!�f�B�t���[�Y�F
	Color4 diffuse;
	//!���ʔ���
	Color4 specular;
	//!�e�N�X�`���[���\���Ă��郁�b�V�����ǂ����̃t���O
	Vector4 texture;
};

/****** End of File *****************************************************/
