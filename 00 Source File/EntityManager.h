/**
* @file EntityManager.h
* @brief マネージャークラス
* @author Ryunosuke Honda.
*/
#pragma once

#include <list>
#include "DefaultDestroy.h"
#include "NoDestroy.h"
#include <iostream>

/**
*	マネージャークラス
*/
template <
	class Entity, // 要素
	class Destroy = DefaultDestroy, // 削除方法を示すポリシークラス
	class List = std::list<Entity> // コンテナの種類を示すポリシークラス
>
class EntityManager
{
public:
	// コンストラクタ
	EntityManager() {}
	// デストラクタ
	~EntityManager()
	{
		//clear();
	}
	// 要素の追加
	void add(Entity entity)
	{
		mEntityList.push_back(entity);
	}
	// 要素数を返す
	unsigned int count() const
	{
		return static_cast<unsigned int>(mEntityList.size());
	}
	// 訪問者の受け入れ
	template <class Visitor>
	void accept(Visitor& visitor)
	{
		for (List::iterator i(mEntityList.begin()); i != mEntityList.end(); ++i)
		{
			visitor.visit(*i);
		}
	}
	// ペア訪問者の受け入れ
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
	// 要素の削除
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

	// 条件にあった要素の数を返す
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

	// 要素の全消去
	void clear()
	{
		for (List::iterator i(mEntityList.begin()); i != mEntityList.end(); ++i)
		{
			delete *i;
		}
		mEntityList.clear();
	}
private:
	// コピー禁止
	EntityManager(const EntityManager& other);
	EntityManager& operator = (const EntityManager& other);
private:
	// 要素リスト
	List mEntityList;
};

/* End of File *****************************************************/