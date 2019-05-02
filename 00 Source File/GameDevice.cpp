/**
* @file GameDevice.cpp
* @brief ゲーム全体で使用するデバイスクラスの管理クラス実装ファイル
* @author Ryunosuke Honda.
*/

#include "GameDevice.h"

GameDevice::GameDevice(const HWND & wnd) :
	mRenderer(wnd),
	mInput(wnd)
{

}

IRenderer & GameDevice::renderer()
{
	return mRenderer;
}

IInput & GameDevice::input()
{
	return mInput;
}

/****** End of File *****************************************************/