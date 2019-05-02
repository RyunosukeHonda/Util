/**
* @file EntityVisitorMemFun1.h
* @brief �����o�֐��|�C���^�K��ҁi����1�j
* @author Ryunosuke Honda.
*/
#pragma once

#include "IEntityVisitor.h"

/**
*	�����o�֐��|�C���^�K��ҁi����1�j
*/
template<
	typename Entity,
	typename First,
	typename void (Entity::*MemFun)(First)
>
class EntityVisitorMemFun1 : public IEntityVisitor<Entity*>
{
public:
	// �R���X�g���N�^
	EntityVisitorMemFun1(First first) :
		mFirst(first)
	{}
	// �K�₷��
	void visit(Entity* entity)
	{
		(entity->*MemFun)(mFirst);
	}
private:
	// ��P����
	First mFirst;
};

/* End of File *****************************************************/