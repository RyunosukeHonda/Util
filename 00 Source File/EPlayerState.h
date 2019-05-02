/**
* @file EPlayerState.h
* @brief プレイヤーの状態列挙型
* @author Ryunosuke Honda.
*/
#pragma once

/**
* @enum EPlayerState
* プレイヤーの状態列挙型
*/
enum EPlayerState
{
	//!待機
	IDLE,
	//!走る
	RUN,
	//!エイミング
	AIMING,
	//!決着
	GAME_SET,
};

/****** End of File *****************************************************/
