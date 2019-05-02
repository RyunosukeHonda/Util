/**
* @file FadeIn.h
* @brief フェードイン処理クラス定義ファイル
* @author Ryunosuke Honda.
*/
#pragma once

#include "AFade.h"

/**
*	フェードインクラス
*	だんだん明るくなる
*/
class FadeIn : public AFade
{
public:
	/**
	* @fn
	*	コンストラクタ
	*/
	FadeIn();

	/**
	* @fn
	* デストラクタ
	*/
	~FadeIn();

	// Fade を介して継承されました
	virtual void draw(IRenderer& renderer) override;

private:
	using base = AFade;
};

/****** End of File *****************************************************/
