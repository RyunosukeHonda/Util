/**
* @file EntityEvaluatorMemFun.h
* @brief �����o�֐��|�C���^�]����
* @author Ryunosuke Honda.
*/
#pragma once

#include "IEntityEvaluator.h"

/**
*	�����o�֐��|�C���^�]����
*/
template<
	typename Entity,
	typename bool (Entity::*MemFun)() const
>
class EntityEvaluatorMemFun : public IEntityEvaluator<Entity*>
{
public:
	// �]������
	bool evaluate(Entity* entity)
	{
		return (entity->*MemFun)();
	}
};

/* End of File *****************************************************/