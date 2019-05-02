/**
* @file SoundLoader.cpp
* @brief サウンド読み込みクラス実装ファイル
* @author Ryunosuke Honda.
*/
#include "SoundLoader.h"

#include "SoundManager.h"
#include "SoundID.h"

SoundLoader::SoundLoader(FileNameContainer<LPSTR>& data) :
	Loader(data)
{
}

void SoundLoader::update()
{
	mEndFlag = true;
	if (mCurrentRead < regMaxNumber())
	{
		SoundManager::instance().load(
			static_cast<SoundID>(mCurrentRead),
			mData[mCurrentRead]);
		mCurrentRead += 1;
		mEndFlag = false;
	}
}

/****** End of File *****************************************************/