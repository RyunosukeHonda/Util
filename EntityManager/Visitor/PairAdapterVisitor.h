/**
* @file PairAdapterVisitor.h
* @brief �y�A�K��ҕϊ��A�_�v�^�N���X
* @author Ryunosuke Honda.
*/
#pragma once

#include "IEntityPairVisitor.h"
#include "IEntityVisitor.h"

/**
*	�y�A�K��ҕϊ��A�_�v�^�N���X
*/
template<
	class Entity, // �v�f
	class PairVisitor = IEntityPairVisitor<Entity>, // �y�A�K���
	class Visitor = IEntityVisitor<Entity> // �K���
>
class PairAdapterVisitor : public Visitor
{
public:
	// �R���X�g���N�^
	PairAdapterVisitor(Entity entity, PairVisitor& pair) :
		mEntity(entity),
		mPairVisitor(pair)
	{}
	// �K�₷��
	void visit(Entity entity)
	{
		mPairVisitor.visit(mEntity, entity);
	}
private:
	// �v�f
	Entity mEntity;
	// �y�A�K���
	PairVisitor& mPairVisitor;
};

/* End of File *****************************************************/