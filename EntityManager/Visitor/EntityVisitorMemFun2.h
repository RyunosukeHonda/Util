/**
* @file EntityVisitorMemFun2.h
* @brief メンバ関数ポインタ訪問者（引数２）
* @author Ryunosuke Honda.
*/
#pragma once

#include "IEntityVisitor.h"

/**
*	メンバ関数ポインタ訪問者（引数２）
*/
template<
	typename Entity,
	typename First,
	typename Second,
	typename void (Entity::*MemFun)(First, Second)
>
class EntityVisitorMemFun2 : public IEntityVisitor<Entity*>
{
public:
	// コンストラクタ
	EntityVisitorMemFun2(First first, Second second) :
		mFirst(first), mSecond(second)
	{}
	// 訪問する
	void visit(Entity* entity)
	{
		(entity->*MemFun)(mFirst, mSecond);
	}
private:
	// 第１引数
	First mFirst;
	// 第２引数
	Second mSecond;
};

/* End of File *****************************************************/