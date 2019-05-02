/**
* @file EntityVisitorMemFun.h
* @brief メンバ関数ポインタ訪問者
* @author Ryunosuke Honda.
*/
#pragma once

#include "IEntityVisitor.h"

/**
*	メンバ関数ポインタ訪問者
*/
template<
	typename Entity,
	typename void (Entity::*MemFun)()
>
class EntityVisitorMemFun : public IEntityVisitor<Entity*>
{
public:
	// 訪問する
	void visit(Entity* entity)
	{
		(entity->*MemFun)();
	}
};

/* End of File *****************************************************/