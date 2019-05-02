/**
* @file TitleIdling.h
* @brief タイトル・待機状態クラス定義ファイル
* @author Ryunosuke Honda.
*/
#pragma once

#include "ITitleState.h"

/**
*	タイトル待機状態クラス
*	入力を待機する状態。
*	入力があるまで特に処理は行わず、
*	入力に対応した状態に移行する
*/
class TitleIdling : public ITitleState
{
public:
	/**
	 * @fn
	 * デフォルトコンストラクタ
	 */
	TitleIdling();

	/**
	 * @fn
	 * デストラクタ
	 */
	~TitleIdling();

	// ITitleState を介して継承されました
	virtual void init() override;

	virtual void shutdown() override;

	virtual bool isEnd() override;

	virtual ETitleState next() override;

	virtual void update(IInput & input) override;

	virtual void draw(IRenderer & renderer) override;

private:
	//!状態終了フラグ
	bool mIsEnd;
};

/* End of File *****************************************************/