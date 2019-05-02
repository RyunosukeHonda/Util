/**
* @file UIImageObject.cpp
* @brief UI�p�摜�I�u�W�F�N�g�N���X�����t�@�C��
* @author Ryunosuke Honda.
*/
#include "UIImageObject.h"

#include "IRenderer.h"

UIImageObject::UIImageObject(const TextureID& id) :
	mDesc(id)
{
	mDesc.mpRect = this;
}

UIImageObject::~UIImageObject()
{
}

void UIImageObject::setID(const TextureID & id)
{
	mDesc.mID = id;
}

void UIImageObject::setColor(const Color4 & color)
{
	mDesc.mDiffuse = color;
}

void UIImageObject::draw(IRenderer & renderer)
{
	renderer.render(&mDesc);
}

/* End of File *****************************************************/