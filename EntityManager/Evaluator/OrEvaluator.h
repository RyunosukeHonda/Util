/**
* @file OrEvaluator.h
* @brief ＯＲ評価者クラス
* @author Ryunosuke Honda.
*/
#pragma once

#include "IEntityEvaluator.h"

/**
*	ＯＲ評価者クラス
*/
template <
	class Entity, 　　　　　　　　　　　　　　　// 要素
	class Evaluator = IEntityEvaluator<Entity>　// 評価者
>
class OrEvaluator : public Evaluator
{
public:
	// コンストラクタ
	OrEvaluator(Evaluator& first, Evaluator& second) :
		mFirst(first), mSecond(second)
	{}
	// 評価する
	bool evaluate(Entity entity)
	{
		if (mFirst.evaluate(entity) == true) {
			return true;
		}
		return mSecond.evaluate(entity);
	}
private:
	// 評価者
	Evaluator& mFirst;
	Evaluator& mSecond;
};

/* End of File *****************************************************/