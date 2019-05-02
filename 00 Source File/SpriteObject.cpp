/**
* @file SpriteObject.cpp
* @brief �X�v���C�g�I�u�W�F�N�g�N���X�����t�@�C��
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