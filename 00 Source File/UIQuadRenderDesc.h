/**
* @file UIQuadRenderDesc
* @brief UI��`�`��L�q�q
* @author Ryunosuke Honda.
*/
#pragma once

#include "ShaderTextureID.h"
#include "RectTransform.h"

/**
*	UI��`�`��L�q�q
*/
struct UIQuadRenderDesc
{
	/**
	* @fn
	* �R���X�g���N�^
	*/
	UIQuadRenderDesc(const ShaderTextureID& id) :
		mID(id),
		mDiffuse(0, 0, 0, 1),
		mpRect(nullptr),
		mTime(0.0f)
	{}

	//!�e�N�X�`���ԍ�
	ShaderTextureID mID;
	//!�f�B�t���[�Y�F
	Color4 mDiffuse;
	//!2D�g�����X�t�H�[��
	RectTransform* mpRect;
	//!�A�j���[�V��������
	float mTime;
};

/****** End of File *****************************************************/
