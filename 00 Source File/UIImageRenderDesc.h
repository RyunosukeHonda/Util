/**
* @file UIImageRenderDesc
* @brief UI�摜�`��L�q�q
* @author Ryunosuke Honda.
*/
#pragma once

#include "TextureID.h"
#include "RectTransform.h"

/**
*	UI�摜�`��L�q�q
*/
struct UIImageRenderDesc
{
	/**
	* @fn
	* �R���X�g���N�^
	*/
	UIImageRenderDesc(const TextureID& id) :
		mID(id),
		mDiffuse(0, 0, 0, 1),
		mpRect(nullptr)
	{}

	//!�e�N�X�`���ԍ�
	TextureID mID;
	//!�f�B�t���[�Y�F
	Color4 mDiffuse;
	//!2D�g�����X�t�H�[��
	RectTransform* mpRect;
};

/****** End of File *****************************************************/
