/**
* @file GameMainSequencer.h
* @brief ゲームメインシーンシーケンサークラス定義ファイル
* @author Ryunosuke Honda.
*/
#pragma once

#include "Base.h"
#include "StateMachineTemplate.h"
#include "IGameMainState.h"

/**
*	ゲームメインシーンシーケンサークラス
*	メイン(バトル)シーンの流れを管理
*/
class GameMainSequencer : public StateMachineTemplate<EGameMainState, IGameMainState>
{
public:
	/**
	 * @fn
	 * デフォルトコンストラクタ
	 */
	GameMainSequencer();

	/**
	 * @fn
	 * デストラクタ
	 */
	~GameMainSequencer();

	/**
	* @fn
	* 現在のステートを更新する
	* @param (input) 入力機能
	*/
	void update(IInput& input);

	/**
	* @fn
	* FPS60矯正更新・物理周りの処理を記述
	* @param (dt) フレーム偏差時間
	*/
	void fixedUpdate(float dt) ;

	/**
	* @fn
	* 遅延更新・updateよりあとに実行したい処理を記述
	* @param (input) 入力インターフェース
	*/
	void lateUpdate(IInput& input);

	/**
	* @fn
	* 現在のステートを描画
	* @param (renderer) レンダラー
	*/
	void draw(IRenderer& renderer);
};

/* End of File *****************************************************/