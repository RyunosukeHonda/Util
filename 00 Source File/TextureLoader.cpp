/**
* @file TextureLoader.cpp
* @brief テクスチャ(スプライト用画像)読み込みクラス実装ファイル
* @author Ryunosuke Honda.
*/
#include "TextureLoader.h"

#include "IRenderer.h"
#include "TextureID.h"

TextureLoader::TextureLoader(IRenderer & renderer, FileNameContainer<LPCWSTR> & data) :
	Loader(data),
	mRenderer(renderer)
{
}

void TextureLoader::update()
{
	mEndFlag = true;
	if (mCurrentRead < regMaxNumber())
	{
		mRenderer.load(static_cast<TextureID>(mCurrentRead), mData[mCurrentRead]);
		mCurrentRead += 1;
		mEndFlag = false;
	}
}

/****** End of File *****************************************************/