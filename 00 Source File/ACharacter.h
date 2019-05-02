/**
* @file ACharacter.h
* @brief キャラクター抽象クラス定義ファイル
* @author Ryunosuke Honda.
*/
#pragma once

#include "IObject.h"
#include "Status.h"

/**
*	抽象キャラクタークラス
*/
class ACharacter : public IObject
{
public:
	/**
	* @fn
	* コンストラクタ
	* @param (hp) 体力
	*/
	ACharacter(int hp);

	/**
	 * @fn
	 * デストラクタ
	 */
	virtual ~ACharacter() {}

	/**
	* @fn
	* 初期化
	*/
	virtual void init() = 0;

	/**
	* @fn
	* 60FPS矯正更新
	*/
	virtual void fixedUpdate(float dt) = 0;

	/**
	* @fn
	* 死亡しているか
	*/
	virtual bool isDead() const;

protected:
	//!ステータス
	Status mStatus;
};

/* End of File *****************************************************/