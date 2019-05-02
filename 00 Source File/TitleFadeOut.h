/**
* @file TitleFadeOut.h
* @brief �^�C�g���E�t�F�[�h�A�E�g��ԃN���X��`�t�@�C��
* @author Ryunosuke Honda.
*/
#pragma once

#include "ITitleState.h"
#include "FadeOut.h"

#include <functional>

/**
*	�^�C�g���E�t�F�[�h�A�E�g��ԃN���X
*	�t�F�[�h�A�E�g�I���Ɠ����ɃV�[�����I���̂�
*	�I���������Ƃ�Ԃ��֐���ێ�����
*/
class TitleFadeOut : public ITitleState
{
public:
	/**
	 * @fn
	 * �f�t�H���g�R���X�g���N�^
	 */
	TitleFadeOut(std::function<void()> endFunc);

	/**
	 * @fn
	 * �f�X�g���N�^
	 */
	~TitleFadeOut();

	// ITitleState ����Čp������܂���
	virtual void init() override;
	virtual void shutdown() override;
	virtual bool isEnd() override;
	virtual ETitleState next() override;
	virtual void update(IInput & input) override;
	virtual void draw(IRenderer & renderer) override;

private:
	//!�I����ʒm����֐���ݒ肷��
	std::function<void()> mEndFunc;
	//!�t�F�[�h�A�E�g�@�\�N���X
	FadeOut mFadeOut;
};

/* End of File *****************************************************/