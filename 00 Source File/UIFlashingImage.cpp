/**
* @file UIFlashingImage.cpp
* @brief UI�摜�ɓ_�ŋ@�\��ǉ������N���X��`�t�@�C��
* @author Ryunosuke Honda.
*/
#include "UIFlashingImage.h"

#include "IRenderer.h"

UIFlashingImage::UIFlashingImage(const TextureID& id, float time) :
	base(id),
	mTimer(time),
	mEnable(true)
{
}

UIFlashingImage::~UIFlashingImage()
{
}

void UIFlashingImage::draw(IRenderer & renderer)
{
	mTimer.update();

	if (mTimer.isEnd())
	{
		mTimer.init();
		mEnable = !mEnable;
	}

	if (!mEnable)return;
	renderer.render(&mDesc);
}

/* End of File *****************************************************/