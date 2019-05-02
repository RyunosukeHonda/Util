/**
* @file InputKey.cpp
* @brief キー入力クラス実装ファイル
* @author Ryunosuke Honda.
*/
#include "InputKey.h"

InputKey::InputKey(LPDIRECTINPUT8 pDinput, const HWND& hwnd) :
	mKeyInfo()
{
	// 「DirectInputデバイス」オブジェクトの作成
	pDinput->CreateDevice(GUID_SysKeyboard, &mpKeyDevice, NULL);

	// デバイスをキーボードに設定
	mpKeyDevice->SetDataFormat(&c_dfDIKeyboard);

	// 協調レベルの設定
	mpKeyDevice->SetCooperativeLevel(hwnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);

	// デバイスを「取得」する
	mpKeyDevice->Acquire();
}

InputKey::~InputKey()
{
	SAFE_RELEASE(mpKeyDevice);
}

void InputKey::update()
{
	//キー入力情報の更新
	HRESULT hr = mpKeyDevice->Acquire();
	if ((hr == DI_OK) || (hr == S_FALSE))
	{
		mpKeyDevice->GetDeviceState(sizeof(diks), &diks);
	}
}

void InputKey::lateUpdate()
{
	//登録されている＝ゲームで使用するキーのみ情報を保存
	for (auto pair : mKeyInfo) {
		mKeyInfo[pair.first] = diks[pair.first] & 0x80;
	}
}

bool InputKey::isKeyDown(KeyCode key)
{
	checkKeyInfoRegister(key);
	return diks[key] & 0x80 && !mKeyInfo[key];
}

bool InputKey::isKeyPress(KeyCode key)
{
	checkKeyInfoRegister(key);
	return diks[key] & 0x80 && mKeyInfo[key];
}

bool InputKey::isKeyUp(KeyCode key)
{
	checkKeyInfoRegister(key);
	return !(diks[key] & 0x80) && mKeyInfo[key];
}

bool InputKey::isKeyRelease(KeyCode key)
{
	checkKeyInfoRegister(key);
	return !(diks[key] & 0x80) && !mKeyInfo[key];
}

void InputKey::checkKeyInfoRegister(KeyCode key)
{
	//キー入力情報保管マップにキーが登録されていなければ
	if (mKeyInfo.count(key) == 0)
	{
		//キーは離されている
		mKeyInfo[key] = false;
	}
}

/* End of File *****************************************************/