/**
* @file EntityVisitorMemFun.h
* @brief �����o�֐��|�C���^�K���
* @author Ryunosuke Honda.
*/
#pragma once

#include "IEntityVisitor.h"

/**
*	�����o�֐��|�C���^�K���
*/
template<
	typename Entity,
	typename void (Entity::*MemFun)()
>
class EntityVisitorMemFun : public IEntityVisitor<Entity*>
{
public:
	// �K�₷��
	void visit(Entity* entity)
	{
		(entity->*MemFun)();
	}
};

/* End of File *****************************************************/