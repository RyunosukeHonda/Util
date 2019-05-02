/**
* @file ShaderConstantBuffer.h
* @brief �V�F�[�_�[�p�̃R���X�^���g�o�b�t�@�[�̃A�v�����\����
* @author Ryunosuke Honda.
*/
#pragma once

#include "MathDef.h"

/**
*	�V�F�[�_�[�p�̃R���X�^���g�o�b�t�@�[�̃A�v�����\����
*/
struct ShaderConstantBuffer
{
	//!���[���h�s��
	Matrix4x4 mW;
	//!���[���h����ˉe�܂ł̕ϊ��s��
	Matrix4x4 mWVP;
	//!���C�g����
	Vector4 vLightDir;
	//!�J�����ʒu
	Vector4 vEye;
};

/****** End of File *****************************************************/
