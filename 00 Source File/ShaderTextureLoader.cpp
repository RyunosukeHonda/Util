/**
* @file ShaderTextureLoader.cpp
* @brief シェーダーテクスチャ(矩形に貼り付ける)読み込みクラス実装ファイル
* @author Ryunosuke Honda.
*/
#include "ShaderTextureLoader.h"

#include "IRenderer.h"
#include "ShaderTextureID.h"

ShaderTextureLoader::ShaderTextureLoader(IRenderer & renderer, FileNameContainer<LPCWSTR> & data) :
	Loader(data),
	mRenderer(renderer)
{
}

ShaderTextureLoader::~ShaderTextureLoader()
{
}

void ShaderTextureLoader::update()
{
	mEndFlag = true;
	if (mCurrentRead < regMaxNumber())
	{
		mRenderer.load(static_cast<ShaderTextureID>(mCurrentRead), mData[mCurrentRead]);
		mCurrentRead += 1;
		mEndFlag = false;
	}
}

/* End of File *****************************************************/