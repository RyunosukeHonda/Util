/**
* @file FadeOut.cpp
* @brief フェードアウト処理クラス実装ファイル
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

	//だんだん暗くなる
	mBG.setColor(Color4(0, 0, 0, mTimer.rate()));
	mBG.draw(renderer);
}

/****** End of File *****************************************************/
