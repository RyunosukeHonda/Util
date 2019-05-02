/**
* @file TitleIdling.cpp
* @brief タイトル・入力待機状態クラス実装ファイル
* @author Ryunosuke Honda.
*/
#include "TitleIdling.h"

#include "IInput.h"
#include <XInput.h>

TitleIdling::TitleIdling() :
	mIsEnd(false)
{
}

TitleIdling::~TitleIdling()
{
}

void TitleIdling::init()
{
	mIsEnd = false;
}

void TitleIdling::shutdown()
{
}

bool TitleIdling::isEnd()
{
	return mIsEnd;
}

ETitleState TitleIdling::next()
{
	return ETitleState::FADEOUT;
}

void TitleIdling::update(IInput & input)
{
	//スタートボタンが押されたら終了
	for (int i = 0; i < GameDef::PLAYER_COUNT; i++)
	{
		if (input.isButtonDown(static_cast<EPlayerIndex>(i), XINPUT_GAMEPAD_START))
		{
			mIsEnd = true;
			break;
		}
	}
}

void TitleIdling::draw(IRenderer & renderer)
{
}

/* End of File *****************************************************/