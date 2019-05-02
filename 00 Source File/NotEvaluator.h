/**
* @file NotEvaluator.h
* @brief �m�n�s�]���҃N���X
* @author Ryunosuke Honda.
*/
#pragma once

#include "IEntityEvaluator.h"

/**
*	�m�n�s�]���҃N���X
*/
template <
	class Entity,
	class Evaluator = IEntityEvaluator<Entity>
>
class NotEvaluator : public Evaluator
{
public:
	// �R���X�g���N�^
	NotEvaluator(Evaluator& evaluator) :
		mEvaluator(evaluator)
	{}
	// �]������
	bool evaluate(Entity entity)
	{
		return !mEvaluator.evaluate(entity);
	}
private:
	// �]����
	Evaluator& mEvaluator;
};

/* End of File *****************************************************/