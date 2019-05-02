/**
* @file FBXHierarchyMeshLoader.cpp
* @brief FBX階層メッシュ読み込みクラス実装ファイル
* @author Ryunosuke Honda.
*/
#include "FBXHierarchyMeshLoader.h"
#include "FBXHierarchyMeshID.h"
#include "IRenderer.h"

FBXHierarchyMeshLoader::FBXHierarchyMeshLoader(IRenderer& renderer, FileNameContainer<CHAR*>& data) :
	Loader(data),
	mRenderer(renderer)
{
}

FBXHierarchyMeshLoader::~FBXHierarchyMeshLoader()
{
}

void FBXHierarchyMeshLoader::update()
{
	mEndFlag = true;
	if (mCurrentRead < regMaxNumber())
	{
		mRenderer.load(static_cast<FBXHierarchyID>(mCurrentRead), mData[mCurrentRead]);
		mCurrentRead += 1;
		mEndFlag = false;
	}
}

/* End of File *****************************************************/