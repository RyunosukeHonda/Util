/**
* @file SpriteConstantBuffer
* @brief �X�v���C�g�`��V�F�[�_�[�ɏ��𑗂�R���X�^���g�o�b�t�@�[
* @author Ryunosuke Honda.
*/
#pragma once

#include "MathDef.h"

/**
*	�X�v���C�g�`��V�F�[�_�[�ɏ��𑗂�R���X�^���g�o�b�t�@�[
*/
struct SpriteConstantBuffer
{
	//!���[���h�s��
	Matrix4x4 mW;
	//!���[���h����ˉe�܂ł̕ϊ��s��
	Matrix4x4 mWVP;
	//!���C�g����
	Vector4 vLightDir;
	//!�g�U����(�F)
	Color4 mColor;
	//!�J�����ʒu
	Vector4 vEye;
};

/****** End of File *****************************************************/
