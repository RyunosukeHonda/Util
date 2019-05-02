/**
* @file UIQuadObject.cpp
* @brief UI用矩形オブジェクトクラス実装ファイル
* @author Ryunosuke Honda.
*/
#include "UIQuadObject.h"

#include "IRenderer.h"

UIQuadObject::UIQuadObject(const ShaderTextureID& id) :
	mDesc(id)
{
	mDesc.mpRect = this;
}

UIQuadObject::~UIQuadObject()
{
}

void UIQuadObject::setColor(Color4 & color)
{
	mDesc.mDiffuse = color;
}

void UIQuadObject::draw(IRenderer & renderer)
{
	mDesc.mTime += 0.01f;
	renderer.render(&mDesc);
}

/* End of File *****************************************************/