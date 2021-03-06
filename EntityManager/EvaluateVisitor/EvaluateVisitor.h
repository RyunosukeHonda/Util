/**
* @file EvaluateVisitor.h
* @brief 評価訪問者クラス
* @author Ryunosuke Honda.
*/
#pragma once

#include "IEntityEvaluator.h"
#include "IEntityVisitor.h"

/**
*	評価訪問者クラス
*/
template<
	class Entity, // 訪問する要素
	class Evaluator = IEntityEvaluator<Entity>, // 評価者
	class Visitor = IEntityVisitor<Entity> // 訪問者
>
class EvaluateVisitor : public Visitor, public Evaluator
{
public:
	// コンストラクタ
	EvaluateVisitor(Evaluator& evaluator, Visitor& visitor) :
		mEvaluator(evaluator), mVisitor(visitor)
	{}
	// 訪問する
	void visit(Entity entity)
	{
		evaluate(entity);
	}
	// 評価する
	bool evaluate(Entity entity)
	{
		// 評価を満たせば，訪問をする
		bool result = mEvaluator.evaluate(entity);
		if (result == true) {
			mVisitor.visit(entity);
		}
		return result;
	}
private:
	// 評価者
	Evaluator& mEvaluator;
	// 訪問者
	Visitor& mVisitor;
};

/* End of File *****************************************************/