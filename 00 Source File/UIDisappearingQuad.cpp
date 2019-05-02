/**
* @file UIDisappearingQuad.cpp
* @brief ���X�ɏ����Ă�����`�G�t�F�N�g�N���X�����t�@�C��
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
	///�֐��Ăяo���̎�Ԃ��Ȃ����ߊe�X�V�����͂����ōs���Ă��܂�

	mTimer.update();
	setColor(Color4(mDesc.mDiffuse.r, mDesc.mDiffuse.g, mDesc.mDiffuse.b, 1.0f - mTimer.rate()));
	renderer.render(&mDesc);
}

/* End of File *****************************************************/