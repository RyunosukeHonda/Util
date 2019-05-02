/**
* @file PairAdapterVisitor.h
* @brief ペア訪問者変換アダプタクラス
* @author Ryunosuke Honda.
*/
#pragma once

#include "IEntityPairVisitor.h"
#include "IEntityVisitor.h"

/**
*	ペア訪問者変換アダプタクラス
*/
template<
	class Entity, // 要素
	class PairVisitor = IEntityPairVisitor<Entity>, // ペア訪問者
	class Visitor = IEntityVisitor<Entity> // 訪問者
>
class PairAdapterVisitor : public Visitor
{
public:
	// コンストラクタ
	PairAdapterVisitor(Entity entity, PairVisitor& pair) :
		mEntity(entity),
		mPairVisitor(pair)
	{}
	// 訪問する
	void visit(Entity entity)
	{
		mPairVisitor.visit(mEntity, entity);
	}
private:
	// 要素
	Entity mEntity;
	// ペア訪問者
	PairVisitor& mPairVisitor;
};

/* End of File *****************************************************/