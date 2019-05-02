/**
* @file AFade.h
* @brief フェード処理基底クラス定義ファイル
* @author Ryunosuke Honda.
*/
#pragma once

#include "Timer.h"
#include "UIQuadObject.h"

/**
*	フェード処理基底クラス
*	継承してdrawの方法を変更し
*	フェードイン、アウトを実装する
*	内容は単純に黒塗りテクスチャのアルファ値をタイマーで操作するだけ
*/
class AFade
{
public:
	/**
	* @fn
	*	コンストラクタ
	*/
	AFade();

	/**
	* @fn
	*	仮想デストラクタ
	*/
	virtual ~AFade() {}

	/**
	* @fn
	* 初期化
	*/
	void init();

	/**
	* @fn
	* フェードの実行。second秒間で処理が行われます
	* @param (second) フェードする時間(秒)
	*/
	void start(float second);

	/**
	* @fn
	* フェードを強制終了

	*/
	void forcedEnd();

	/**
	* @fn
	* フェードが終了したかどうか
	*/
	bool isEnd();

	/**
	* @fn
	* 更新・タイマーを進める
	*/
	void update();

	/**
	* @fn
	* 描画
	* @param (renderer) レンダラー
	*/
	virtual void draw(IRenderer& renderer) = 0;

protected:
	//!タイマー
	Timer mTimer;
	//!稼働中か
	bool mIsWorking;
	//!単色背景
	UIQuadObject mBG;
};

/****** End of File *****************************************************/
