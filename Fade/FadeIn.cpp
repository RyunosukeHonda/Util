/**
* @file FadeIn.cpp
* @brief �t�F�[�h�C�������N���X�����t�@�C��
* @author Ryunosuke Honda.
*/
#include "FadeIn.h"

FadeIn::FadeIn():
	base()
{
}

FadeIn::~FadeIn()
{
}

void FadeIn::draw(IRenderer& renderer)
{
	if (!mIsWorking) return;

	//���񂾂񖾂邭����
	mBG.setColor(Color4(0, 0, 0, 1.0f - mTimer.rate()));
	mBG.draw(renderer);
}

/****** End of File *****************************************************/
