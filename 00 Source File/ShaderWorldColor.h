/**
* @file ShaderWorldColor.h
* @brief �V�F�[�_�[�p�̃R���X�^���g�o�b�t�@�[�̃A�v�����\����
* @author Ryunosuke Honda.
*/
#pragma once

#include "MathDef.h"

/**
*	�V�F�[�_�[�p�̃R���X�^���g�o�b�t�@�[�̃A�v�����\����
*/
struct ShaderWorldColor
{
	//!���[���h�s��
	Matrix4x4 mW;
	//!���[���h����ˉe�܂ł̕ϊ��s��
	Matrix4x4 mWVP;
	//!�A���r�G���g��
	Color4 ambient;
	//!�f�B�t���[�Y�F
	Color4 diffuse;
	//!���ʔ���
	Color4 specular;
};

/****** End of File *****************************************************/
