/**
* @file PlaneCollider.cpp
* @brief 平面コライダークラス実装ファイル
* @author Ryunosuke Honda.
*/
#include "PlaneCollider.h"

#include "Collision.h"

PlaneCollider::PlaneCollider(const Vector3& pos, const Vector3& norm):
	base(ERigidType::PLANE)
{
	LocalPosition = pos;
	//上方向ベクトルを法線ベクトルとして使用する
	mUp = norm;
}

PlaneCollider::~PlaneCollider()
{
}

/* End of File *****************************************************/