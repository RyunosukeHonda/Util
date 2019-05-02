/**
* @file SpriteObject.cpp
* @brief スプライトオブジェクトクラス実装ファイル
* @author Ryunosuke Honda.
*/
#include "SpriteObject.h"

#include "IRenderer.h"

SpriteObject::SpriteObject(const TextureID& id) :
	mDesc(id)
{
	mDesc.mpTransform = this;
}

SpriteObject::~SpriteObject()
{
}

void SpriteObject::setColor(const Color4 & color)
{
	mDesc.mDiffuse = color;
}

void SpriteObject::draw(IRenderer & renderer)
{
	renderer.render(&mDesc);
}

/* End of File *****************************************************/