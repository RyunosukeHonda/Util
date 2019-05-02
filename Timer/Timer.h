/**
* @file Timer.h
* @brief 汎用タイマークラス(加算式)定義ファイル
* @author Ryunosuke Honda.
*/
#pragma once

#include "Base.h"

/**
*	汎用タイマークラス(加算式)
*	フレーム数などに影響されないよう
*	実時間で計測します
*/
class Timer
{
private:
	const int ToDWORD = 1000;
	const float ToSecond = 1.0f / (float)ToDWORD;

public:
	/**
	* @fn
	* コンストラクタ
	* @brief １秒に設定
	*/
	Timer();

	/**
	* @fn
	* コンストラクタ
	* @brief 初期時間設定用
	* @param (limit) 制限時間 
	*/
	Timer(float limit);

	/**
	* @fn
	* デストラクタ
	*/
	~Timer();
	
	/**
	* @fn
	* 初期化
	* @brief 制限時間をリセット
	*/
	void init();

	/**
	* @fn
	* 初期化
	* @brief 制限時間を設定してリセット
	* @param (limit) 設定する制限時間
	*/
	void init(float limit);

	/**
	* @fn
	* 更新
	*/
	void update();

	/**
	* @fn
	* タイマー終了判定
	* @return 制限時間が経過したかどうか
	*/
	bool isEnd();

	/**
	* @fn
	* 現在時間 / 制限時間　の割合を返す
	* @return 現在時間 / 制限時間
	* @detail 0.0f～1.0f
	*/
	float rate();

	/**
	* @fn
	* 現在時間取得
	* @return 現在時間
	*/
	float getCurrent();

	/**
	* @fn
	* タイマーを強制終了する
	*/
	void forcedEnd();
	
private:
	//!制限時間
	DWORD mLimit;	
	//!現在時間
	DWORD mCurrent;	
    //!開始時の時刻を格納
	DWORD mStart;	
};

/****** End of File *****************************************************/
