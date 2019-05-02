/**
* @file NotEvaluator.h
* @brief ‚m‚n‚s•]‰¿ŽÒƒNƒ‰ƒX
* @author Ryunosuke Honda.
*/
#pragma once

#include "IEntityEvaluator.h"

/**
*	‚m‚n‚s•]‰¿ŽÒƒNƒ‰ƒX
*/
template <
	class Entity,
	class Evaluator = IEntityEvaluator<Entity>
>
class NotEvaluator : public Evaluator
{
public:
	// ƒRƒ“ƒXƒgƒ‰ƒNƒ^
	NotEvaluator(Evaluator& evaluator) :
		mEvaluator(evaluator)
	{}
	// •]‰¿‚·‚é
	bool evaluate(Entity entity)
	{
		return !mEvaluator.evaluate(entity);
	}
private:
	// •]‰¿ŽÒ
	Evaluator& mEvaluator;
};

/* End of File *****************************************************/