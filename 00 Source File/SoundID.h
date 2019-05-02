/**
* @file SoundID.h
* @brief 音リソースID列挙型
* @author Ryunosuke Honda.
*/
#pragma once

/**
* @enum SoundID
* 音リソースID列挙型
*/
enum class SoundID : unsigned int
{
	//!BGM
	BGM,
	//!射撃音
	FIRE,
	//!命中音
	HIT,
	//!ゲームオーバー
	GAMEOVER,
	//!読み込み終了
	END,
};

/****** End of File *****************************************************/
