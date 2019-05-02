/**
* @file FadeOut.h
* @brief フェードアウト処理クラス定義ファイル
* @author Ryunosuke Honda.
*/
#pragma once

#include "AFade.h"

/**
*	フェードアウト処理クラス
*	徐々に暗くなる
*/
class FadeOut : public AFade
{
public:
	/**
	* @fn
	*	コンストラクタ
	*/
	FadeOut();

	/**
	* @fn
	* 仮想デストラクタ
	*/
	~FadeOut();

	// Fade を介して継承されました
	virtual void draw(IRenderer& renderer) override;

private:
	using base = AFade;
};

/****** End of File *****************************************************/
