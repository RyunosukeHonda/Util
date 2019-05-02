/**
* @file OBJStaticMeshLoader.cpp
* @brief OBJ形式スタティックメッシュ読み込みクラス実装ファイル
* @author Ryunosuke Honda.
*/
#include "OBJStaticMeshLoader.h"
#include "IRenderer.h"

#include "OBJStaticMeshID.h"

OBJStaticMeshLoader::OBJStaticMeshLoader(IRenderer& renderer, FileNameContainer<LPSTR>& data) :
	Loader(data),
	mRenderer(renderer)
{
}

void OBJStaticMeshLoader::update()
{
	mEndFlag = true;
	if (mCurrentRead < regMaxNumber())
	{
		mRenderer.load(static_cast<OBJMeshID>(mCurrentRead), mData[mCurrentRead]);
		mCurrentRead += 1;
		mEndFlag = false;
	}
}

/****** End of File *****************************************************/