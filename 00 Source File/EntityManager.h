/**
* @file EntityManager.h
* @brief �}�l�[�W���[�N���X
* @author Ryunosuke Honda.
*/
#pragma once

#include <list>
#include "DefaultDestroy.h"
#include "NoDestroy.h"
#include <iostream>

/**
*	�}�l�[�W���[�N���X
*/
template <
	class Entity, // �v�f
	class Destroy = DefaultDestroy, // �폜���@�������|���V�[�N���X
	class List = std::list<Entity> // �R���e�i�̎�ނ������|���V�[�N���X
>
class EntityManager
{
public:
	// �R���X�g���N�^
	EntityManager() {}
	// �f�X�g���N�^
	~EntityManager()
	{
		//clear();
	}
	// �v�f�̒ǉ�
	void add(Entity entity)
	{
		mEntityList.push_back(entity);
	}
	// �v�f����Ԃ�
	unsigned int count() const
	{
		return static_cast<unsigned int>(mEntityList.size());
	}
	// �K��҂̎󂯓���
	template <class Visitor>
	void accept(Visitor& visitor)
	{
		for (List::iterator i(mEntityList.begin()); i != mEntityList.end(); ++i)
		{
			visitor.visit(*i);
		}
	}
	// �y�A�K��҂̎󂯓���
	template <class PairVisitor>
	void acceptPair(PairVisitor& pair)
	{
		for (List::iterator i(mEntityList.begin()); i != mEntityList.end(); ++i)
		{
			List::iterator j(i);
			for (++j; j != mEntityList.end(); ++j)
			{
				pair.visit(*i, *j);
			}
		}
	}
	// �v�f�̍폜
	template <class Evaluator>
	void remove(Evaluator& evaluator)
	{
		List::iterator i(mEntityList.begin());
		while (i != mEntityList.end()) {
			if (evaluator.evaluate(*i) == true)
			{
				Destroy::destroy(i);
				i = mEntityList.erase(i);
			}
			else
			{
				++i;
			}
		}
	}

	// �����ɂ������v�f�̐���Ԃ�
	template <class Evaluator>
	int find(Evaluator& evaluator)
	{
		int count = 0;
		List::iterator i(mEntityList.begin());
		while (i != mEntityList.end()) {
			if (evaluator.evaluate(*i) == true)
			{
				count++;
			}
			i++;
		}
		return count;
	}

	// �v�f�̑S����
	void clear()
	{
		for (List::iterator i(mEntityList.begin()); i != mEntityList.end(); ++i)
		{
			delete *i;
		}
		mEntityList.clear();
	}
private:
	// �R�s�[�֎~
	EntityManager(const EntityManager& other);
	EntityManager& operator = (const EntityManager& other);
private:
	// �v�f���X�g
	List mEntityList;
};

/* End of File *****************************************************/