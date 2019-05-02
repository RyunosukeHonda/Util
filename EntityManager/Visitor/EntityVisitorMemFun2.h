/**
* @file EntityVisitorMemFun2.h
* @brief �����o�֐��|�C���^�K��ҁi�����Q�j
* @author Ryunosuke Honda.
*/
#pragma once

#include "IEntityVisitor.h"

/**
*	�����o�֐��|�C���^�K��ҁi�����Q�j
*/
template<
	typename Entity,
	typename First,
	typename Second,
	typename void (Entity::*MemFun)(First, Second)
>
class EntityVisitorMemFun2 : public IEntityVisitor<Entity*>
{
public:
	// �R���X�g���N�^
	EntityVisitorMemFun2(First first, Second second) :
		mFirst(first), mSecond(second)
	{}
	// �K�₷��
	void visit(Entity* entity)
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