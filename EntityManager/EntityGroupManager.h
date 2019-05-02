/**
* @file EntityGroupManager.h
* @brief �O���[�v�}�l�[�W���[�N���X
* @author Ryunosuke Honda.
*/
#pragma once

#include "EntityManager.h"
#include <unordered_map>

/**
*	�O���[�v�}�l�[�W���[�N���X
*/
template <
	class Entity, // �v�f
	class Destroy = NoDestroy, // �폜���@�������|���V�[�N���X
	class GroupID = int, // �O���[�v�h�c
	class Manager = EntityManager<Entity, Destroy>, // �}�l�[�W���[
	class Map = std::unordered_map<GroupID, Manager*> // �}�b�v
>
class EntityGroupManager
{
public:
	// �R���X�g���N�^
	EntityGroupManager() {}
	// �f�X�g���N�^
	~EntityGroupManager()
	{
		clear();
	}
	// �O���[�v���擾
	Manager& operator [] (const GroupID& id)
	{
		// �O���[�v�����݂��Ȃ���ΐV�K�ɍ쐬
		if (mGroup[id] == 0) {
			mGroup[id] = new Manager();
		}
		return *mGroup[id];
	}
	// �v�f�����J�E���g����
	unsigned int count() const
	{
		unsigned int result = 0;
		for (Map::const_iterator i(mGroup.begin()); i != mGroup.end(); ++i) {
			result += (*i).second->count();
		}
		return result;
	}
	// �S�Ă̗v�f���폜
	void clear()
	{
		for (Map::iterator i(mGroup.begin()); i != mGroup.end(); ++i) {
			delete (*i).second;
		}
		mGroup.clear();
	}
	// �K��҂̎󂯓���
	template <class Visitor>
	void accept(Visitor& visitor)
	{
		for (Map::iterator i(mGroup.begin()); i != mGroup.end(); ++i) {
			(*i).second->accept(visitor);
		}
	}
	// �v�f�̍폜
	template <class Evaluator>
	void remove(Evaluator& evaluator)
	{
		for (Map::iterator i(mGroup.begin()); i != mGroup.end(); ++i) {
			(*i).second->remove(evaluator);
		}
	}
	// �y�A�K��҂̎󂯓���
	template <class PairVisitor>
	void acceptPair(Manager& first, Manager& second, PairVisitor& pair)
	{
		PairManagerVisitor<Entity, Manager, PairVisitor> visitor(second, pair);
		first.accept(visitor);
	}
	// �y�A�K��҂̎󂯓���
	template <class PairVisitor>
	void acceptPair(PairVisitor& pair)
	{
		for (Map::iterator i(mGroup.begin()); i != mGroup.end(); ++i) {
			// ����O���[�v���y�A�ŖK��
			(*i).second->acceptPair(pair);
			// ���̃O���[�v���y�A�ŖK��
			Map::iterator j(i);
			for (++j; j != mGroup.end(); ++j) {
				acceptPair(*(*i).second, *(*j).second, pair);
			}
		}
	}
private:
	// �R�s�[�֎~
	EntityGroupManager(const EntityGroupManager& other);
	EntityGroupManager& operator = (const EntityGroupManager& other);
private:
	// �}�l�[�W���[�O���[�v
	Map mGroup;
};

/* End of File *****************************************************/