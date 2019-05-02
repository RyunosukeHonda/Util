/**
* @file QuadObject.cpp
* @brief 矩形オブジェクトクラス
* @author Ryunosuke Honda.
*/
#include "QuadObject.h"

#include "IRenderer.h"

QuadObject::QuadObject(const ShaderTextureID& id) :
	mDesc(id)
{
	mDesc.mpTransform = this;
}

QuadObject::~QuadObject()
{
}

void QuadObject::setColor(const Color4 & color)
{
	mDesc.mDiffuse = color;
}

void QuadObject::draw(IRenderer & renderer)
{
	renderer.render(&mDesc);
}

/* End of File *****************************************************/