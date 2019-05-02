/**
* @file InputMouse.cpp
* @brief マウス入力クラス実装ファイル
* @author Ryunosuke Honda.
*/
#include "InputMouse.h"
#include "Screen.h"

InputMouse::InputMouse(LPDIRECTINPUT8 pDinput, const HWND& hwnd) :
	mMouseInfo(),
	dims()
{
	// 「DirectInputデバイス」オブジェクトの作成
	pDinput->CreateDevice(GUID_SysMouse, &mpMouseDevice, NULL);
	// デバイスをマウスに設定
	mpMouseDevice->SetDataFormat(&c_dfDIMouse2);
	// 協調レベルの設定
	mpMouseDevice->SetCooperativeLevel(hwnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	// デバイスを「取得」する
	mpMouseDevice->Acquire();

	//マウス情報マップに予め初期情報を登録
	mMouseInfo[EMouseButton::LEFT] = false;
	mMouseInfo[EMouseButton::RIGHT] = false;
	mMouseInfo[EMouseButton::CENTER] = false;
}

InputMouse::~InputMouse()
{
}

void InputMouse::update()
{
	//マウス入力情報の更新
	if (FAILED(mpMouseDevice->GetDeviceState(sizeof(DIMOUSESTATE2), &dims)))
	{
		mpMouseDevice->Acquire();
		return;
	}

	mPos.x += dims.lX;
	mPos.y += dims.lY;

	if (mPos.x < 0)
	{
		mPos.x = 0;
	}
	else if (mPos.x > Screen::WINDOW_WIDTH)
	{
		mPos.x = Screen::WINDOW_WIDTH;
	}
	if (mPos.y < 0)
	{
		mPos.y = 0;
	}
	else if (mPos.y > Screen::WINDOW_HEIGHT)
	{
		mPos.y = Screen::WINDOW_HEIGHT;
	}

}

void InputMouse::lateUpdate()
{
	//マウスの各情報を格納
	//左ボタン
	mMouseInfo[EMouseButton::LEFT] = dims.rgbButtons[EMouseButton::LEFT] & 0x80;
	//右ボタン
	mMouseInfo[EMouseButton::RIGHT] = dims.rgbButtons[EMouseButton::RIGHT] & 0x80;
	//中ボタン
	mMouseInfo[EMouseButton::CENTER] = dims.rgbButtons[EMouseButton::CENTER] & 0x80;
}

bool InputMouse::isMouseButtonDown(EMouseButton mouse)
{
	//今フレーム押されていて、前フレームで押されていなければtrue
	return dims.rgbButtons[mouse] & 0x80 && !mMouseInfo[mouse];
}

bool InputMouse::isMouseButtonPress(EMouseButton mouse)
{
	//今フレーム押されていて、前フレームでも押されていればtrue
	return dims.rgbButtons[mouse] & 0x80 && mMouseInfo[mouse];
}

bool InputMouse::isMouseButtonUp(EMouseButton mouse)
{
	//今フレーム押されていない時、前フレームで押されていればtrue
	return dims.rgbButtons[mouse] == 0x00 && mMouseInfo[mouse];
}

bool InputMouse::isMouseButtonRelease(EMouseButton mouse)
{
	//今フレーム押されていない時、前フレームでも押されていなければtrue
	return dims.rgbButtons[mouse] == 0x00 && !mMouseInfo[mouse];
}

/* End of File *****************************************************/