/**
* @file EGameMainState.h
* @brief ゲームメインシーン状態列挙型
* @author Ryunosuke Honda.
*/
#pragma once

/**
* @enum EGameMainState
* ゲームメインシーン状態列挙型
*/
enum EGameMainState
{
	//!スタート前のカウントダウン
	COUNTDOWN,
	//!バトル中
	BATTLE,
	//!決着演出
	GAMESET,
};

/****** End of File *****************************************************/
