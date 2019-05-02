/**
* @file TitleFadeOut.h
* @brief タイトル・フェードアウト状態クラス定義ファイル
* @author Ryunosuke Honda.
*/
#pragma once

#include "ITitleState.h"
#include "FadeOut.h"

#include <functional>

/**
*	タイトル・フェードアウト状態クラス
*	フェードアウト終了と同時にシーンが終わるので
*	終了したことを返す関数を保持する
*/
class TitleFadeOut : public ITitleState
{
public:
	/**
	 * @fn
	 * デフォルトコンストラクタ
	 */
	TitleFadeOut(std::function<void()> endFunc);

	/**
	 * @fn
	 * デストラクタ
	 */
	~TitleFadeOut();

	// ITitleState を介して継承されました
	virtual void init() override;
	virtual void shutdown() override;
	virtual bool isEnd() override;
	virtual ETitleState next() override;
	virtual void update(IInput & input) override;
	virtual void draw(IRenderer & renderer) override;

private:
	//!終了を通知する関数を設定する
	std::function<void()> mEndFunc;
	//!フェードアウト機能クラス
	FadeOut mFadeOut;
};

/* End of File *****************************************************/