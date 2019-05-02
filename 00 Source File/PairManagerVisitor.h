/**
* @file PairManagerVisitor.h
* @brief ペアマネージャー訪問者クラス
* @author Ryunosuke Honda.
*/
#pragma once

#include "EntityManager.h"
#include "IEntityPairVisitor.h"
#include "IEntityVisitor.h"
#include "PairAdapterVisitor.h"

/**
*	ペアマネージャー訪問者クラス
*/
template<
	class Entity, // 要素
	class Manager = EntityManager<Entity, NoDestroy>, // マネージャー
	class PairVisitor = IEntityPairVisitor<Entity>, // ペア訪問者
	class Visitor = IEntityVisitor<Entity> // 訪問者
>
class PairManagerVisitor : public Visitor
{
public:
	// コンストラクタ
	PairManagerVisitor(Manager& manager, PairVisitor& pair) :
		mManager(manager), 
		mPairVisitor(pair)
	{}
	// 訪問する
	void visit(Entity entity)
	{
		// ペア訪問者を変換する
		PairAdapterVisitor<Entity, PairVisitor, Visitor> visitor(entity, mPairVisitor);
		mManager.accept(visitor);
	}
private:
	// マネージャー
	Manager& mManager;
	// ペア訪問者
	PairVisitor& mPairVisitor;
};

/* End of File *****************************************************/