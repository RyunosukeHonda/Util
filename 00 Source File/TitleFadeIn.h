/**
* @file TitleFadeIn.h
* @brief �^�C�g���E�t�F�[�h�C����ԃN���X��`�t�@�C��
* @author Ryunosuke Honda.
*/
#pragma once

#include "ITitleState.h"
#include "FadeIn.h"

/**
*	�^�C�g���E�t�F�[�h�C����ԃN���X
*	�t�F�[�h�C�����s���A���͂�����΃X�L�b�v����
*/
class TitleFadeIn : public ITitleState
{
public:
	/**
	 * @fn
	 * �f�t�H���g�R���X�g���N�^
	 */
	TitleFadeIn();
	/**
	 * @fn
	 * �f�X�g���N�^
	 */
	~TitleFadeIn();

	// ITitleState ����Čp������܂���
	virtual void init() override;
	virtual void shutdown() override;
	virtual bool isEnd() override;
	virtual ETitleState next() override;
	virtual void update(IInput & input) override;
	virtual void draw(IRenderer & renderer) override;

private:
	//!�t�F�[�h�C���@�\�N���X
	FadeIn mFadeIn;
};

/* End of File *****************************************************/