/**
* @file FBXSkinMeshLoader.cpp
* @brief FBXスキンメッシュ読み込みクラス実装ファイル
* @author Ryunosuke Honda.
*/
#include "FBXSkinMeshLoader.h"
#include "FBXSkinMeshID.h"
#include "IRenderer.h"

FBXSkinMeshLoader::FBXSkinMeshLoader(IRenderer& renderer, FileNameContainer<LPSTR>& data):
	Loader(data),
	mRenderer(renderer)
{
}

FBXSkinMeshLoader::~FBXSkinMeshLoader()
{
}

void FBXSkinMeshLoader::update()
{
	mEndFlag = true;
	if (mCurrentRead < regMaxNumber())
	{
		mRenderer.load(static_cast<FBXSkinID>(mCurrentRead), mData[mCurrentRead]);
		mCurrentRead += 1;
		mEndFlag = false;
	}
}

/* End of File *****************************************************/