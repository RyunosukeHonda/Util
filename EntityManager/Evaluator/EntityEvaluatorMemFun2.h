/**
* @file EntityEvaluatorMemFun2.h
* @brief �����o�֐��|�C���^�K��ҁi�����Q�j
* @author Ryunosuke Honda.
*/
#pragma once

#include "IEntityEvaluator.h"

/**
*	�����o�֐��|�C���^�K��ҁi�����Q�j
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
	// �R���X�g���N�^
	EntityEvaluatorMemFun2(First first, Second second) :
		mFirst(first), mSecond(second)
	{}
	// �]������
	bool evaluate(Entity* entity)
	{
		(entity->*MemFun)(mFirst, mSecond);
	}
private:
	// ��P����
	First mFirst;
	// ��Q����
	Second mSecond;
};

/* End of File *****************************************************/