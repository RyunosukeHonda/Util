/**
* @file EvaluateVisitor.h
* @brief �]���K��҃N���X
* @author Ryunosuke Honda.
*/
#pragma once

#include "IEntityEvaluator.h"
#include "IEntityVisitor.h"

/**
*	�]���K��҃N���X
*/
template<
	class Entity, // �K�₷��v�f
	class Evaluator = IEntityEvaluator<Entity>, // �]����
	class Visitor = IEntityVisitor<Entity> // �K���
>
class EvaluateVisitor : public Visitor, public Evaluator
{
public:
	// �R���X�g���N�^
	EvaluateVisitor(Evaluator& evaluator, Visitor& visitor) :
		mEvaluator(evaluator), mVisitor(visitor)
	{}
	// �K�₷��
	void visit(Entity entity)
	{
		evaluate(entity);
	}
	// �]������
	bool evaluate(Entity entity)
	{
		// �]���𖞂����΁C�K�������
		bool result = mEvaluator.evaluate(entity);
		if (result == true) {
			mVisitor.visit(entity);
		}
		return result;
	}
private:
	// �]����
	Evaluator& mEvaluator;
	// �K���
	Visitor& mVisitor;
};

/* End of File *****************************************************/