/**
* @file AndEvaluator.h
* @brief ‚`‚m‚c•]‰¿ŽÒƒNƒ‰ƒX
* @author Ryunosuke Honda.
*/
#pragma once

#include "IEntityEvaluator.h"

/**
*	‚`‚m‚c•]‰¿ŽÒƒNƒ‰ƒX
*/
template <
	class Entity, // —v‘f
	class Evaluator = IEntityEvaluator<Entity> // •]‰¿ŽÒ
>
class AndEvaluator : public Evaluator
{
public:
	// ƒRƒ“ƒXƒgƒ‰ƒNƒ^
	AndEvaluator(Evaluator& first, Evaluator& second) :
		mFirst(first), mSecond(second)
	{}
	// •]‰¿‚·‚é
	bool evaluate(Entity entity)
	{
		if (mFirst.evaluate(entity) == true) {
			return mSecond.evaluate(entity);
		}
		return false;
	}
private:
	// •]‰¿ŽÒ
	Evaluator& mFirst;
	Evaluator& mSecond;
};

/* End of File *****************************************************/