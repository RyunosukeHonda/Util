/**
* @file IGameMainState.h
* @brief ゲームメイン状態インターフェース
* @author Ryunosuke Honda.
*/
#pragma once

#include "IState.h"
#include "EGameMainState.h"

class IInput;
class IRenderer;

/**
*	ゲームメイン状態インターフェース
*/
class IGameMainState : public IState<EGameMainState>
{
public:
	/**
	 * @fn
	 * 仮想デストラクタ
	 */
	virtual ~IGameMainState() {}

	/**
	* @fn
	* 更新
	* @param (input) 入力インターフェース
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
	*/
	virtual void lateUpdate(IInput& input) = 0;

	/**
	* @fn
	* 描画
	* @param (renderer) レンダラー
	*/
	virtual void draw(IRenderer& renderer) = 0;
};

/* End of File *****************************************************/