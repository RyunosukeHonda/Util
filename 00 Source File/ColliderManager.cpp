/**
* @file ColliderManager.cpp
* @brief コライダー管理クラス実装ファイル
* @author Ryunosuke Honda.
*/
#include "ColliderManager.h"

#include "ACollider.h"
#include "PairManagerVisitor.h"
#include "EntityEvaluatorMemFun.h"
#include "CollisionVisitor.h"

ColliderManager::ColliderManager()
{
}

ColliderManager::~ColliderManager()
{
}

void ColliderManager::add(ACollider * collider)
{
	mColliders[static_cast<unsigned int>(collider->Layer)].add(collider);
}

void ColliderManager::init()
{
	mColliders[ELayer::BULLET1].clear();
	mColliders[ELayer::BULLET2].clear();
}

void ColliderManager::collision()
{
	EntityEvaluatorMemFun<ACollider, &ACollider::isInvalid> invalid;
	mColliders.remove(invalid);

	//衝突判定実行
	CollisionVisitor col;
	mColliders.acceptPair(mColliders[ELayer::DEFAULT], mColliders[ELayer::TEAM1], col);
	mColliders.acceptPair(mColliders[ELayer::DEFAULT], mColliders[ELayer::TEAM2], col);
	mColliders.acceptPair(mColliders[ELayer::DEFAULT], mColliders[ELayer::BULLET1], col);
	mColliders.acceptPair(mColliders[ELayer::DEFAULT], mColliders[ELayer::BULLET2], col);
	mColliders.acceptPair(mColliders[ELayer::TEAM1], mColliders[ELayer::BULLET2], col);
	mColliders.acceptPair(mColliders[ELayer::TEAM2], mColliders[ELayer::BULLET1], col);
}

/* End of File *****************************************************/