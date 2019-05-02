/**
* @file GameDevice.h
* @brief ゲームデバイスクラス定義ファイル
* @author Ryunosuke Honda.
*/
#pragma once

#include "IGameDevice.h"
#include "Renderer.h"
#include "SoundManager.h"
#include "InputManager.h"
#include "UtilMacro.h"

/**
*	ゲームデバイスクラス
*/
class GameDevice : public IGameDevice
{
	COPY_PROTECTED(GameDevice)

public:
	/**
	* @fn
	* コンストラクタ
	* @param (wnd) ウィンドウ情報
	*/
	GameDevice(const HWND& wnd);

	// IGameDevice を介して継承されました
	virtual IRenderer & renderer() override;

	virtual IInput & input() override;

private:
	//!レンダラー
	Renderer mRenderer;
	//!入力
	InputManager mInput;
};

/****** End of File *****************************************************/