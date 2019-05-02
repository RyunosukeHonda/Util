/**
* @file FBXHierarchyMeshLoader.cpp
* @brief FBX�K�w���b�V���ǂݍ��݃N���X�����t�@�C��
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