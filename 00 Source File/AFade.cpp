/**
* @file AFade.cpp
* @brief フェード基底クラス実装ファイル
* @author Ryunosuke Honda.
*/
#include "AFade.h"

#include "ShaderTextureID.h"
#include "Screen.h"

AFade::AFade() :
	mTimer(),
	mIsWorking(false),
	mBG(ShaderTextureID::MONOCHROME)
{
	//背景パラメーターの設定
	mBG.Position = { 0, 0 };
	mBG.Scale = { (float)Screen::WINDOW_WIDTH, (float)Screen::WINDOW_HEIGHT };
	mBG.SortingLayer = 5;
}

void AFade::init()
{
	mTimer.init();
	mIsWorking = false;
}

void AFade::start(float second)
{
	if (mIsWorking) return;

	mTimer.init(second);
	mIsWorking = true;
}

void AFade::forcedEnd()
{
	mTimer.forcedEnd();
}

bool AFade::isEnd()
{
	return mTimer.isEnd();
}

void AFade::update()
{
	if (!mIsWorking)return;

	mTimer.update();
}

/****** End of File *****************************************************/
