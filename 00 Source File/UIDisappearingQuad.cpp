/**
* @file UIDisappearingQuad.cpp
* @brief 徐々に消えていく矩形エフェクトクラス実装ファイル
* @author Ryunosuke Honda.
*/
#include "UIDisappearingQuad.h"

#include "IRenderer.h"

UIDisappearingQuad::UIDisappearingQuad(const ShaderTextureID& id, float disappearingTime) :
	base(id),
	mTimer(),
	mInitTime(disappearingTime)
{
	mTimer.forcedEnd();
}

UIDisappearingQuad::~UIDisappearingQuad()
{
}

void UIDisappearingQuad::init()
{
	mTimer.init(mInitTime);
}

void UIDisappearingQuad::draw(IRenderer & renderer)
{
	///関数呼び出しの手間を省くため各更新処理はここで行ってしまう

	mTimer.update();
	setColor(Color4(mDesc.mDiffuse.r, mDesc.mDiffuse.g, mDesc.mDiffuse.b, 1.0f - mTimer.rate()));
	renderer.render(&mDesc);
}

/* End of File *****************************************************/