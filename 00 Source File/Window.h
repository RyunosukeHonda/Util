/**
* @file Window.h
* @brief �A�v���P�[�V�����̃E�B���h�E�𐶐�����N���X��`�t�@�C��
* @author Ryunosuke Honda.
*/
#pragma once
#include "Base.h"

/**
*	�E�B���h�E�N���X
*/
class Window : public CElement
{
public:
	/**
	* @fn
	* �E�B���h�E�������E����
	*/
	HRESULT InitWindow(HINSTANCE,INT,INT,LPCWSTR);

	///�ȉ��v���p�e�B

	//!�E�B���h�E
	PROPERTY_READONLY(HWND, Wnd);
};

/****** End of File *****************************************************/