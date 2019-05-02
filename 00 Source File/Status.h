/**
* @file Status.h
* @brief ステータスクラス定義ファイル
* 体力などキャラクターに持たせたい値とその振る舞いを実装
* @author Ryunosuke Honda.
*/
#pragma once

#include "Base.h"

class IRenderer;

/**
*	ステータスクラス
*/
class Status : public CElement
{
public:
	/**
	* @fn
	* コンストラクタ
	* @param (hp) 体力
	*/
	Status(int hp);

	/**
	 * @fn
	 * デストラクタ
	 */
	~Status();

	/**
	* @fn
	* ステータス初期化
	*/
	void init();

	/**
	* @fn
	* ダメージを与える(HPを減らす)
	* @param (damage) 与えるダメージ量
	*/
	void damage(const int& damage);

	/**
	* @fn
	* 死亡しているか判定
	* @return 死亡していればtrue
	*/
	bool isDead() const;

	/**
	* @fn
	* 死亡しているか判定
	* @return 死亡していればtrue
	*/
	void draw(IRenderer& renderer) const;

private:
	//!ヒットポイント
	int mHP;
	//!ヒットポイント最大値・初期化用に保存
	int mMaxHP;
};

/* End of File *****************************************************/