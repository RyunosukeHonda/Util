/**
* @file IShotable.h
* @brief 射撃機能インターフェース
* @author Ryunosuke Honda.
*/
#pragma once

#include "Base.h"

class Transform;

/**
*	射撃機能インターフェース
*	プレイヤーが弾丸を撃つのに使用します
*/
class IShotable : public CElement
{
public:
	/**
	 * @fn
	 * 仮想デストラクタ
	 */
	virtual ~IShotable() {}

	/**
	* @fn
	* 射撃する
	* @param (引数名) 持ち主のトランスフォーム情報
	*/
	virtual void shot(const Transform* parent) = 0;
	
	/**
	* @fn
	* 更新処理・レートタイマーの更新などに使用
	*/
	virtual void update() = 0;
};

/* End of File *****************************************************/