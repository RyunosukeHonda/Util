/**
* @file UIAppearingImage.cpp
* @brief ���X�Ɍ����摜�G�t�F�N�g�N���X��`�t�@�C��
* @author Ryunosuke Honda.
*/
#include "UIAppearingImage.h"

#include "IRenderer.h"

UIAppearingImage::UIAppearingImage(const TextureID& id, float appearingTime):
	base(id),
	mTimer(),
	mInitTime(appearingTime)
{
	mTimer.forcedEnd();
}

UIAppearingImage::~UIAppearingImage()
{
}

void UIAppearingImage::init()
{
	mTimer.init(mInitTime);
}

void UIAppearingImage::draw(IRenderer & renderer)
{
	///�֐��Ăяo���̎�Ԃ��Ȃ����ߊe�X�V�����͂����ōs���Ă��܂�

	mTimer.update();
	setColor(Color4(mDesc.mDiffuse.r, mDesc.mDiffuse.g, mDesc.mDiffuse.b, mTimer.rate()));
	renderer.render(&mDesc);
}

/* End of File *****************************************************/