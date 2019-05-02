/**
* @file ITitleState.h
* @brief タイトル状態インターフェース
* @author Ryunosuke Honda.
*/
#pragma once

#include "Base.h"

#include "IState.h"
#include "ETitleState.h"

class IInput;
class IRenderer;

/**
*	タイトル状態インターフェース
*/
class ITitleState : public IState<ETitleState>
{
public:
	/**
	 * @fn
	 * 仮想デストラクタ
	 */
	virtual ~ITitleState() {}

	/**
	* @fn
	* 更新
	* @param (input) 入力機能
	*/
	virtual void update(IInput& input) = 0;

	/**
	* @fn
	* 描画
	* @param (renderer) レンダラー
	*/
	virtual void draw(IRenderer& renderer) = 0;
};

/* End of File *****************************************************/