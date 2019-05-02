/**
* @file TitleSequencer.h
* @brief タイトルシーケンサークラス定義ファイル
* @author Ryunosuke Honda.
*/
#pragma once

#include "Base.h"
#include "StateMachineTemplate.h"
#include "ITitleState.h"

/**
*	タイトルシーケンサークラス
*	タイトルシーンの流れを管理
*/
class TitleSequencer : public StateMachineTemplate<ETitleState, ITitleState>
{
public:
	/**
	 * @fn
	 * デフォルトコンストラクタ
	 */
	TitleSequencer();

	/**
	 * @fn
	 * デストラクタ
	 */
	~TitleSequencer();

	/**
	* @fn
	* 現在のステートを更新する
	* @param (input) 入力機能
	*/
	void update(IInput& input);

	/**
	* @fn
	* 現在のステートを描画
	* @param (renderer) レンダラー
	*/
	void draw(IRenderer& renderer);
};

/* End of File *****************************************************/