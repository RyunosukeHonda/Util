/**
* @file TitleFadeOut.cpp
* @brief タイトル・フェードアウト状態クラス実装ファイル
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
	//このステート終了時にはシーンが遷移するため実際に遷移はしない
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