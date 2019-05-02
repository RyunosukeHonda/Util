/**
* @file FadeIn.cpp
* @brief フェードイン処理クラス実装ファイル
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

	//だんだん明るくする
	mBG.setColor(Color4(0, 0, 0, 1.0f - mTimer.rate()));
	mBG.draw(renderer);
}

/****** End of File *****************************************************/
