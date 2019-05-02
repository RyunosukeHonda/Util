/**
* @file EntityEvaluatorMemFun1.h
* @brief メンバ関数ポインタ評価者（引数１つ）
* @author Ryunosuke Honda.
*/
#pragma once

#include "IEntityEvaluator.h"

/**
*	メンバ関数ポインタ評価者（引数１つ）
*/
template<
	typename Entity,
	typename First,
	typename bool (Entity::*MemFun)(First) const
>
class EntityEvaluatorMemFun1 : public IEntityEvaluator<Entity*>
{
public:
	// コンストラクタ
	EntityEvaluatorMemFun1(First first) :
		mFirst(first)
	{}
	// 評価する
	bool evaluate(Entity* entity)
	{
		return (entity->*MemFun)(mFirst);
	}
private:
	// 第１引数
	First mFirst;
};

/* End of File *****************************************************/