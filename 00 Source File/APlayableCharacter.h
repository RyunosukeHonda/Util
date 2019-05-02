/**
* @file APlayableCharacter.h
* @brief 操作可能な抽象キャラクタークラス定義ファイル
* @author Ryunosuke Honda.
*/
#pragma once

#include "IObject.h"
#include "Status.h"

class IInput;

/**
*	操作可能な抽象キャラクタークラス
*/
class APlayableCharacter : public IObject
{
public:
	/**
	* @fn
	* コンストラクタ
	* @param (hp) 体力
	*/
	APlayableCharacter(int hp);

	/**
	 * @fn
	 * 仮想デストラクタ
	 */
	virtual ~APlayableCharacter() {}

	/**
	* @fn
	* 初期化
	*/
	virtual void init() = 0;

	/**
	* @fn
	* 更新処理
	*/
	virtual void update(IInput& input) = 0;

	/**
	* @fn
	* update後に処理される更新処理
	*/
	virtual void lateUpdate(IInput& input) = 0;

	/**
	* @fn
	* 60FPS矯正更新
	*/
	virtual void fixedUpdate(float dt) = 0;

	/**
	* @fn
	* 描画実行
	* @brief このゲームではプレイヤーの目線がそのままカメラになるため、
	* 保持しているカメラ目線で描画を実行してもらう
	* @param (renderer) レンダラー
	*/
	virtual void renderExecute(IRenderer& renderer) = 0;

	/**
	* @fn
	* 死亡しているか
	*/
	virtual bool isDead() const;

	/**
	* @fn
	* ゲーム決着時処理
	*/
	virtual void gameSet() = 0;

protected:
	//!ステータス
	Status mStatus;
};

/* End of File *****************************************************/