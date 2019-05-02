/**
* @file EntityEvaluatorMemFun1.h
* @brief �����o�֐��|�C���^�]���ҁi�����P�j
* @author Ryunosuke Honda.
*/
#pragma once

#include "IEntityEvaluator.h"

/**
*	�����o�֐��|�C���^�]���ҁi�����P�j
*/
template<
	typename Entity,
	typename First,
	typename bool (Entity::*MemFun)(First) const
>
class EntityEvaluatorMemFun1 : public IEntityEvaluator<Entity*>
{
public:
	// �R���X�g���N�^
	EntityEvaluatorMemFun1(First first) :
		mFirst(first)
	{}
	// �]������
	bool evaluate(Entity* entity)
	{
		return (entity->*MemFun)(mFirst);
	}
private:
	// ��P����
	First mFirst;
};

/* End of File *****************************************************/