/**
* @file EntityVisitorMemFun1.h
* @brief メンバ関数ポインタ訪問者（引数1）
* @author Ryunosuke Honda.
*/
#pragma once

#include "IEntityVisitor.h"

/**
*	メンバ関数ポインタ訪問者（引数1）
*/
template<
	typename Entity,
	typename First,
	typename void (Entity::*MemFun)(First)
>
class EntityVisitorMemFun1 : public IEntityVisitor<Entity*>
{
public:
	// コンストラクタ
	EntityVisitorMemFun1(First first) :
		mFirst(first)
	{}
	// 訪問する
	void visit(Entity* entity)
	{
		(entity->*MemFun)(mFirst);
	}
private:
	// 第１引数
	First mFirst;
};

/* End of File *****************************************************/