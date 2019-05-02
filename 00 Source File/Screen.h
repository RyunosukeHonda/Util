/**
* @file Screen.h
* @brief スクリーンサイズ定義ファイル
* @author Ryunosuke Honda.
*/
#pragma once

/**
*	スクリーンサイズ定義
*	(値の実装はcppで行っています)
*/
class Screen
{
public:
	//! ウィンドウ幅
	static const unsigned int WINDOW_WIDTH = 1280;
	//! ウィンドウ高さ
	static const unsigned int WINDOW_HEIGHT = 720;
	//! Field Of View
	static float FOV;
	//! ニアークリップ
	static float NEAR_;
	//! ファークリップ
	static float FAR_;
};


/****** End of File *****************************************************/
