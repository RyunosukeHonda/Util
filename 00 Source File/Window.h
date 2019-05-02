/**
* @file Window.h
* @brief アプリケーションのウィンドウを生成するクラス定義ファイル
* @author Ryunosuke Honda.
*/
#pragma once
#include "Base.h"

/**
*	ウィンドウクラス
*/
class Window : public CElement
{
public:
	/**
	* @fn
	* ウィンドウ初期化・生成
	*/
	HRESULT InitWindow(HINSTANCE,INT,INT,LPCWSTR);

	///以下プロパティ

	//!ウィンドウ
	PROPERTY_READONLY(HWND, Wnd);
};

/****** End of File *****************************************************/