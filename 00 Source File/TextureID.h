/**
* @file TextureID.h
* @brief テクスチャ管理番号列挙型
* @author Ryunosuke Honda.
*/
#pragma once

/**
* @enum TextureID
* テクスチャ管理番号列挙型
*/
enum TextureID : unsigned int
{
	//!NowLoading...
	LOADDING = 0,
	//!ゲームタイトルロゴ画像
	GAME_LOGO,
	//!PressStartButton...
	PRESS_START_BUTTON,
	//!ゲームメイン画面のターゲットマーカー
	MARKER,
	//!1
	COUNT_ONE,	
	//!2
	COUNT_TWO,
	//!3
	COUNT_THREE,
	//!START!!
	START,
	//!YouWin!!
	WIN,
	//!YouLose...
	LOSE,
};

/****** End of File *****************************************************/
