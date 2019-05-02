/**
* @file QuadConstantBuffer
* @brief ��`�`��V�F�[�_�[�ɏ��𑗂�R���X�^���g�o�b�t�@�[
* @author Ryunosuke Honda.
*/
#pragma once

#include "MathDef.h"

/**
*	��`�`��V�F�[�_�[�ɏ��𑗂�R���X�^���g�o�b�t�@�[
*/
struct QuadConstantBuffer
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
	//!�V�F�[�_�[���̃A�j���[�V��������
	Vector4 mTime;
};

/****** End of File *****************************************************/
