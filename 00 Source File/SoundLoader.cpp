/**
* @file SoundLoader.cpp
* @brief �T�E���h�ǂݍ��݃N���X�����t�@�C��
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