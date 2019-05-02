/**
* @file TitleFadeIn.h
* @brief タイトル・フェードイン状態クラス定義ファイル
* @author Ryunosuke Honda.
*/
#pragma once

#include "ITitleState.h"
#include "FadeIn.h"

/**
*	タイトル・フェードイン状態クラス
*	フェードインを行い、入力があればスキップする
*/
class TitleFadeIn : public ITitleState
{
public:
	/**
	 * @fn
	 * デフォルトコンストラクタ
	 */
	TitleFadeIn();
	/**
	 * @fn
	 * デストラクタ
	 */
	~TitleFadeIn();

	// ITitleState を介して継承されました
	virtual void init() override;
	virtual void shutdown() override;
	virtual bool isEnd() override;
	virtual ETitleState next() override;
	virtual void update(IInput & input) override;
	virtual void draw(IRenderer & renderer) override;

private:
	//!フェードイン機能クラス
	FadeIn mFadeIn;
};

/* End of File *****************************************************/