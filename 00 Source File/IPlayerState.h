/**
* @file IPlayerState.h
* @brief プレイヤーの状態インターフェース
* @author Ryunosuke Honda.
*/
#pragma once

#include "Base.h"
#include "IState.h"
#include "EPlayerState.h"

class IInput;
class IRenderer;
class ACollider;

/**
*	プレイヤー状態インターフェース	
*/
class IPlayerState : public IState<EPlayerState>
{
public:
	/**
	 * @fn
	 * 仮想デストラクタ
	 */
	virtual ~IPlayerState() {}

	/**
	* @fn
	* 更新
	* @param (input) 入力インターフェース
	* @param (sound) サウンドインターフェース
	*/
	virtual void update(IInput& input) = 0;

	/**
	* @fn
	* FPS60矯正更新・物理周りの処理を記述
	* @param (dt) フレーム偏差時間
	*/
	virtual void fixedUpdate(float dt) = 0;

	/**
	* @fn
	* 遅延更新・updateよりあとに実行したい処理を記述
	* @param (input) 入力インターフェース
	* @param (sound) サウンドインターフェース
	*/
	virtual void lateUpdate(IInput& input) = 0;

	/**
	* @fn
	* 描画
	* @param (renderer) レンダラー
	*/
	virtual void draw(IRenderer& renderer) = 0;

	/**
	* @fn
	* 衝突時イベント
	* @param (other) 衝突相手
	*/
	virtual void onCollisionEnter(ACollider * other) = 0;

	/**
	* @fn
	* 決着状態に強制移行する
	*/
	virtual void gameSet() = 0;
};

/* End of File *****************************************************/