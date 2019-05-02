/**
* @file UIAppearingImage.cpp
* @brief 徐々に現れる画像エフェクトクラス定義ファイル
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
	///関数呼び出しの手間を省くため各更新処理はここで行ってしまう

	mTimer.update();
	setColor(Color4(mDesc.mDiffuse.r, mDesc.mDiffuse.g, mDesc.mDiffuse.b, mTimer.rate()));
	renderer.render(&mDesc);
}

/* End of File *****************************************************/