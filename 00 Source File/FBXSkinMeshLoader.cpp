/**
* @file FBXSkinMeshLoader.cpp
* @brief FBX�X�L�����b�V���ǂݍ��݃N���X�����t�@�C��
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