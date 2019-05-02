/**
* @file FadeIn.h
* @brief �t�F�[�h�C�������N���X��`�t�@�C��
* @author Ryunosuke Honda.
*/
#pragma once

#include "AFade.h"

/**
*	�t�F�[�h�C���N���X
*	���񂾂񖾂邭�Ȃ�
*/
class FadeIn : public AFade
{
public:
	/**
	* @fn
	*	�R���X�g���N�^
	*/
	FadeIn();

	/**
	* @fn
	* �f�X�g���N�^
	*/
	~FadeIn();

	// Fade ����Čp������܂���
	virtual void draw(IRenderer& renderer) override;

private:
	using base = AFade;
};

/****** End of File *****************************************************/
