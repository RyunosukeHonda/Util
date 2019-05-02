/**
* @file TitleIdling.h
* @brief �^�C�g���E�ҋ@��ԃN���X��`�t�@�C��
* @author Ryunosuke Honda.
*/
#pragma once

#include "ITitleState.h"

/**
*	�^�C�g���ҋ@��ԃN���X
*	���͂�ҋ@�����ԁB
*	���͂�����܂œ��ɏ����͍s�킸�A
*	���͂ɑΉ�������ԂɈڍs����
*/
class TitleIdling : public ITitleState
{
public:
	/**
	 * @fn
	 * �f�t�H���g�R���X�g���N�^
	 */
	TitleIdling();

	/**
	 * @fn
	 * �f�X�g���N�^
	 */
	~TitleIdling();

	// ITitleState ����Čp������܂���
	virtual void init() override;

	virtual void shutdown() override;

	virtual bool isEnd() override;

	virtual ETitleState next() override;

	virtual void update(IInput & input) override;

	virtual void draw(IRenderer & renderer) override;

private:
	//!��ԏI���t���O
	bool mIsEnd;
};

/* End of File *****************************************************/