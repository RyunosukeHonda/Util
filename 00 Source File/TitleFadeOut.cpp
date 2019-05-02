/**
* @file TitleFadeOut.cpp
* @brief �^�C�g���E�t�F�[�h�A�E�g��ԃN���X�����t�@�C��
* @author Ryunosuke Honda.
*/
#include "TitleFadeOut.h"

TitleFadeOut::TitleFadeOut(std::function<void()> endFunc) :
	mEndFunc(endFunc),
	mFadeOut()
{
}

TitleFadeOut::~TitleFadeOut()
{
}

void TitleFadeOut::init()
{
	mFadeOut.init();
	mFadeOut.start(2.0f);
}

void TitleFadeOut::shutdown()
{
}

bool TitleFadeOut::isEnd()
{
	return mFadeOut.isEnd();
}

ETitleState TitleFadeOut::next()
{
	//���̃X�e�[�g�I�����ɂ̓V�[�����J�ڂ��邽�ߎ��ۂɑJ�ڂ͂��Ȃ�
	return ETitleState::FADEIN;
}


void TitleFadeOut::update(IInput & input)
{
	mFadeOut.update();

	if (mFadeOut.isEnd())
	{
		mEndFunc();
	}
}

void TitleFadeOut::draw(IRenderer & renderer)
{
	mFadeOut.draw(renderer);
}

/* End of File *****************************************************/