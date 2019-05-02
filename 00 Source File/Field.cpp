/**
* @file Field.cpp
* @brief ステージモデルクラス実装ファイル
* @author Ryunosuke Honda.
*/
#include "Field.h"

#include "IRenderer.h"

Field::Field() :
	base(Vector3(0, 0, 0), Vector3(0, 1, 0)),
	mDesc(OBJMeshID::field)
{
	mTag = ETag::GROUND;
	mLayer = ELayer::DEFAULT;
	mDesc.mpTransform = this;
}

Field::~Field()
{
}

void Field::draw(IRenderer & renderer)
{
	renderer.render(&mDesc);
}

/* End of File *****************************************************/