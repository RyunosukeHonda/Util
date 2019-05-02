/**
* @file EntityGroupManager.h
* @brief グループマネージャークラス
* @author Ryunosuke Honda.
*/
#pragma once

#include "EntityManager.h"
#include <unordered_map>

/**
*	グループマネージャークラス
*/
template <
	class Entity, // 要素
	class Destroy = NoDestroy, // 削除方法を示すポリシークラス
	class GroupID = int, // グループＩＤ
	class Manager = EntityManager<Entity, Destroy>, // マネージャー
	class Map = std::unordered_map<GroupID, Manager*> // マップ
>
class EntityGroupManager
{
public:
	// コンストラクタ
	EntityGroupManager() {}
	// デストラクタ
	~EntityGroupManager()
	{
		clear();
	}
	// グループを取得
	Manager& operator [] (const GroupID& id)
	{
		// グループが存在しなければ新規に作成
		if (mGroup[id] == 0) {
			mGroup[id] = new Manager();
		}
		return *mGroup[id];
	}
	// 要素数をカウントする
	unsigned int count() const
	{
		unsigned int result = 0;
		for (Map::const_iterator i(mGroup.begin()); i != mGroup.end(); ++i) {
			result += (*i).second->count();
		}
		return result;
	}
	// 全ての要素を削除
	void clear()
	{
		for (Map::iterator i(mGroup.begin()); i != mGroup.end(); ++i) {
			delete (*i).second;
		}
		mGroup.clear();
	}
	// 訪問者の受け入れ
	template <class Visitor>
	void accept(Visitor& visitor)
	{
		for (Map::iterator i(mGroup.begin()); i != mGroup.end(); ++i) {
			(*i).second->accept(visitor);
		}
	}
	// 要素の削除
	template <class Evaluator>
	void remove(Evaluator& evaluator)
	{
		for (Map::iterator i(mGroup.begin()); i != mGroup.end(); ++i) {
			(*i).second->remove(evaluator);
		}
	}
	// ペア訪問者の受け入れ
	template <class PairVisitor>
	void acceptPair(Manager& first, Manager& second, PairVisitor& pair)
	{
		PairManagerVisitor<Entity, Manager, PairVisitor> visitor(second, pair);
		first.accept(visitor);
	}
	// ペア訪問者の受け入れ
	template <class PairVisitor>
	void acceptPair(PairVisitor& pair)
	{
		for (Map::iterator i(mGroup.begin()); i != mGroup.end(); ++i) {
			// 同一グループをペアで訪問
			(*i).second->acceptPair(pair);
			// 他のグループをペアで訪問
			Map::iterator j(i);
			for (++j; j != mGroup.end(); ++j) {
				acceptPair(*(*i).second, *(*j).second, pair);
			}
		}
	}
private:
	// コピー禁止
	EntityGroupManager(const EntityGroupManager& other);
	EntityGroupManager& operator = (const EntityGroupManager& other);
private:
	// マネージャーグループ
	Map mGroup;
};

/* End of File *****************************************************/