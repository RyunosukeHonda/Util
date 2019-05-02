/**
* @file EntityEvaluatorMemFun2.h
* @brief メンバ関数ポインタ訪問者（引数２つ）
* @author Ryunosuke Honda.
*/
#pragma once

#include "IEntityEvaluator.h"

/**
*	メンバ関数ポインタ訪問者（引数２つ）
*/
template<
	typename Entity,
	typename First,
	typename Second,
	typename bool (Entity::*MemFun)(First, Second) const
>
class EntityEvaluatorMemFun2 : public IEntityEvaluator<Entity*>
{
public:
	// コンストラクタ
	EntityEvaluatorMemFun2(First first, Second second) :
		mFirst(first), mSecond(second)
	{}
	// 評価する
	bool evaluate(Entity* entity)
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