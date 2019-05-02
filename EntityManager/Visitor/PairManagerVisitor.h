/**
* @file PairManagerVisitor.h
* @brief �y�A�}�l�[�W���[�K��҃N���X
* @author Ryunosuke Honda.
*/
#pragma once

#include "EntityManager.h"
#include "IEntityPairVisitor.h"
#include "IEntityVisitor.h"
#include "PairAdapterVisitor.h"

/**
*	�y�A�}�l�[�W���[�K��҃N���X
*/
template<
	class Entity, // �v�f
	class Manager = EntityManager<Entity, NoDestroy>, // �}�l�[�W���[
	class PairVisitor = IEntityPairVisitor<Entity>, // �y�A�K���
	class Visitor = IEntityVisitor<Entity> // �K���
>
class PairManagerVisitor : public Visitor
{
public:
	// �R���X�g���N�^
	PairManagerVisitor(Manager& manager, PairVisitor& pair) :
		mManager(manager), 
		mPairVisitor(pair)
	{}
	// �K�₷��
	void visit(Entity entity)
	{
		// �y�A�K��҂�ϊ�����
		PairAdapterVisitor<Entity, PairVisitor, Visitor> visitor(entity, mPairVisitor);
		mManager.accept(visitor);
	}
private:
	// �}�l�[�W���[
	Manager& mManager;
	// �y�A�K���
	PairVisitor& mPairVisitor;
};

/* End of File *****************************************************/