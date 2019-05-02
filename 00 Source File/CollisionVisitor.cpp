/**
* @file CollisionVisitor.cpp
* @brief コライダー管理クラスで衝突判定を行う訪問者クラス実装ファイル
* @author Ryunosuke Honda.
*/
#include "CollisionVisitor.h"

#include "Collision.h"
#include "SphereCollider.h"
#include "PlaneCollider.h"

void CollisionVisitor::visit(ACollider* c1, ACollider* c2)
{
	//ダウンキャストを行うが、dynamic_castは使いたくないので
	//形状で分岐、安全なstatic_castを行う
	
	///c1が球の場合
	if (c1->Type == ERigidType::SPHERE)
	{
		///c2が球の場合
		if (c2->Type == ERigidType::SPHERE)
		{
			Collision::instance().collision(static_cast<SphereCollider*>(c1), static_cast<SphereCollider*>(c2));
			return;
		}
		///c2が平面の場合
		if (c2->Type == ERigidType::PLANE)
		{
			Collision::instance().collision(static_cast<SphereCollider*>(c1), static_cast<PlaneCollider*>(c2));
			return;
		}
	}

	///c1が平面の場合
	if (c1->Type == ERigidType::PLANE)
	{
		///c2が球の場合
		if (c2->Type == ERigidType::SPHERE)
		{
			Collision::instance().collision(static_cast<SphereCollider*>(c2), static_cast<PlaneCollider*>(c1));
			return;
		}
		///c2が平面の場合
		if (c2->Type == ERigidType::PLANE)
		{
			Collision::instance().collision(static_cast<PlaneCollider*>(c1), static_cast<PlaneCollider*>(c2));
			return;
		}
	}
}

/* End of File *****************************************************/