/**
* @file ShaderTextureLoader.cpp
* @brief �V�F�[�_�[�e�N�X�`��(��`�ɓ\��t����)�ǂݍ��݃N���X�����t�@�C��
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