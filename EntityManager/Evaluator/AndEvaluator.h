/**
* @file AndEvaluator.h
* @brief �`�m�c�]���҃N���X
* @author Ryunosuke Honda.
*/
#pragma once

#include "IEntityEvaluator.h"

/**
*	�`�m�c�]���҃N���X
*/
template <
	class Entity, // �v�f
	class Evaluator = IEntityEvaluator<Entity> // �]����
>
class AndEvaluator : public Evaluator
{
public:
	// �R���X�g���N�^
	AndEvaluator(Evaluator& first, Evaluator& second) :
		mFirst(first), mSecond(second)
	{}
	// �]������
	bool evaluate(Entity entity)
	{
		if (mFirst.evaluate(entity) == true) {
			return mSecond.evaluate(entity);
		}
		return false;
	}
private:
	// �]����
	Evaluator& mFirst;
	Evaluator& mSecond;
};

/* End of File *****************************************************/