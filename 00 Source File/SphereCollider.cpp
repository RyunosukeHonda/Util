/**
* @file SphereCollider.cpp
* @brief 境界球コライダークラス実装ファイル
* @author Ryunosuke Honda.
*/
#include "SphereCollider.h"

#include "Collision.h"

SphereCollider::SphereCollider(float radius) :
	base(ERigidType::SPHERE),
	mRadius(radius)
{
}

SphereCollider::~SphereCollider()
{
}

/* End of File *****************************************************/