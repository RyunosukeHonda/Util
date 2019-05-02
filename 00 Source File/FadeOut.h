/**
* @file FadeOut.h
* @brief �t�F�[�h�A�E�g�����N���X��`�t�@�C��
* @author Ryunosuke Honda.
*/
#pragma once

#include "AFade.h"

/**
*	�t�F�[�h�A�E�g�����N���X
*	���X�ɈÂ��Ȃ�
*/
class FadeOut : public AFade
{
public:
	/**
	* @fn
	*	�R���X�g���N�^
	*/
	FadeOut();

	/**
	* @fn
	* ���z�f�X�g���N�^
	*/
	~FadeOut();

	// Fade ����Čp������܂���
	virtual void draw(IRenderer& renderer) override;

private:
	using base = AFade;
};

/****** End of File *****************************************************/
