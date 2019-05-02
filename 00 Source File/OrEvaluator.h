/**
* @file OrEvaluator.h
* @brief �n�q�]���҃N���X
* @author Ryunosuke Honda.
*/
#pragma once

#include "IEntityEvaluator.h"

/**
*	�n�q�]���҃N���X
*/
template <
	class Entity, �@�@�@�@�@�@�@�@�@�@�@�@�@�@�@// �v�f
	class Evaluator = IEntityEvaluator<Entity>�@// �]����
>
class OrEvaluator : public Evaluator
{
public:
	// �R���X�g���N�^
	OrEvaluator(Evaluator& first, Evaluator& second) :
		mFirst(first), mSecond(second)
	{}
	// �]������
	bool evaluate(Entity entity)
	{
		if (mFirst.evaluate(entity) == true) {
			return true;
		}
		return mSecond.evaluate(entity);
	}
private:
	// �]����
	Evaluator& mFirst;
	Evaluator& mSecond;
};

/* End of File *****************************************************/