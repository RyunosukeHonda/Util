/**
* @file EvaluateVisitor.h
* @brief •]‰¿–K–âÒƒNƒ‰ƒX
* @author Ryunosuke Honda.
*/
#pragma once

#include "IEntityEvaluator.h"
#include "IEntityVisitor.h"

/**
*	•]‰¿–K–âÒƒNƒ‰ƒX
*/
template<
	class Entity, // –K–â‚·‚é—v‘f
	class Evaluator = IEntityEvaluator<Entity>, // •]‰¿Ò
	class Visitor = IEntityVisitor<Entity> // –K–âÒ
>
class EvaluateVisitor : public Visitor, public Evaluator
{
public:
	// ƒRƒ“ƒXƒgƒ‰ƒNƒ^
	EvaluateVisitor(Evaluator& evaluator, Visitor& visitor) :
		mEvaluator(evaluator), mVisitor(visitor)
	{}
	// –K–â‚·‚é
	void visit(Entity entity)
	{
		evaluate(entity);
	}
	// •]‰¿‚·‚é
	bool evaluate(Entity entity)
	{
		// •]‰¿‚ğ–‚½‚¹‚ÎC–K–â‚ğ‚·‚é
		bool result = mEvaluator.evaluate(entity);
		if (result == true) {
			mVisitor.visit(entity);
		}
		return result;
	}
private:
	// •]‰¿Ò
	Evaluator& mEvaluator;
	// –K–âÒ
	Visitor& mVisitor;
};

/* End of File *****************************************************/