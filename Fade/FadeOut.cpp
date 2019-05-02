/**
* @file FadeOut.cpp
* @brief �t�F�[�h�A�E�g�����N���X�����t�@�C��
* @author Ryunosuke Honda.
*/
#include "FadeOut.h"

FadeOut::FadeOut() :
	base()
{
}

FadeOut::~FadeOut()
{
}

void FadeOut::draw(IRenderer& renderer)
{
	if (!mIsWorking)return;

	//���񂾂�Â��Ȃ�
	mBG.setColor(Color4(0, 0, 0, mTimer.rate()));
	mBG.draw(renderer);
}

/****** End of File *****************************************************/
