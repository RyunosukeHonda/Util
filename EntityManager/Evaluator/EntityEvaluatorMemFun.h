/**
* @file EntityEvaluatorMemFun.h
* @brief メンバ関数ポインタ評価者
* @author Ryunosuke Honda.
*/
#pragma once

#include "IEntityEvaluator.h"

/**
*	メンバ関数ポインタ評価者
*/
template<
	typename Entity,
	typename bool (Entity::*MemFun)() const
>
class EntityEvaluatorMemFun : public IEntityEvaluator<Entity*>
{
public:
	// 評価する
	bool evaluate(Entity* entity)
	{
		return (entity->*MemFun)();
	}
};

/* End of File *****************************************************/