/**
* @file TextRenderDesc.h
* @brief �e�L�X�g�`��p�L�q�q
* @author Ryunosuke Honda.
*/
#pragma once

#include "Base.h"
#include <string>

/**
*	�e�L�X�g�`��p�L�q�q�\����
*/
struct TextRenderDesc
{
public:
	/**
	*	@fn
	*	�R���X�g���N�^
	*/
	TextRenderDesc() :
		position(0, 0),
		text(""),
		color(1, 1, 1, 1)
	{}

	//!�`��ʒu(�X�N���[�����W)
	Vector2 position;
	//!�`��e�L�X�g
	string text;
	//!�`��F
	D3DXCOLOR color;
};

/****** End of File *****************************************************/
