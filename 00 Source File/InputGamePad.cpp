/**
* @file InputGamePad.cpp
* @brief ゲームパッド入力機能クラス実装ファイル
* @author Ryunosuke Honda.
*/
#include "InputGamePad.h"

const float InputGamePad::STICK_MAX = 65535.0f / 2.0f;
const float InputGamePad::TRIGGER_MAX = 255.0f;

InputGamePad::InputGamePad() :
	mGamePadInfo(),
	mButtons(),
	mLeftSticks(),
	mRightSticks()
{
	//コントローラー最大数分ループ
	for (DWORD i = 0; i < MAX_CONTROLLERS; i++)
	{
		///配列外参照を防ぐために予め空データを登録しておく
		mGamePadInfo.push_back(GamePadInfoMap());
		mButtons.push_back(0);
		mLeftSticks.push_back(Vector2());
		mRightSticks.push_back(Vector2());
	}
}

InputGamePad::~InputGamePad()
{
}

void InputGamePad::update()
{
	//接続確認
	checkConnect();

	//コントローラー最大数分ループ
	for (DWORD i = 0; i < MAX_CONTROLLERS; i++)
	{
		//接続されていなければ処理しない
		if (!GAME_PAD[i].bConnected) break;

		//ボタン入力情報更新
		mButtons[i] = GAME_PAD[i].state.Gamepad.wButtons;

		//アナログ入力情報更新・0~1の間の値になるよう矯正
		//感度が高すぎるので0.1未満は０に矯正
		mLeftSticks[i].x = abs(((float)GAME_PAD[i].state.Gamepad.sThumbLX / STICK_MAX)) < 0.2f ? 0.0f : (float)GAME_PAD[i].state.Gamepad.sThumbLX / STICK_MAX;
		mLeftSticks[i].y = abs(((float)GAME_PAD[i].state.Gamepad.sThumbLY / STICK_MAX)) < 0.2f ? 0.0f : (float)GAME_PAD[i].state.Gamepad.sThumbLY / STICK_MAX;;
		mRightSticks[i].x = abs(((float)GAME_PAD[i].state.Gamepad.sThumbRX / STICK_MAX)) < 0.2f ? 0.0 : (float)GAME_PAD[i].state.Gamepad.sThumbRX / STICK_MAX;;
		mRightSticks[i].y = abs(((float)GAME_PAD[i].state.Gamepad.sThumbRY / STICK_MAX)) < 0.2f ? 0.0 : (float)GAME_PAD[i].state.Gamepad.sThumbRY / STICK_MAX;;
	}
}

void InputGamePad::lateUpdate()
{
	//登録されている＝ゲームで使用するキーのみ情報を保存
	for (DWORD i = 0; i < MAX_CONTROLLERS; i++)
	{
		for (auto pair : mGamePadInfo[i])
		{
			mGamePadInfo[i][pair.first] = mButtons[i] & pair.first;
		}
	}
}

bool InputGamePad::isButtonDown(const EPlayerIndex& index, const GamePadButton button)
{
	checkButtonInfoRegister(index, button);
	return mButtons[index] & button && !mGamePadInfo[index][button];
}

bool InputGamePad::isButtonPress(const EPlayerIndex& index, const GamePadButton button)
{
	checkButtonInfoRegister(index, button);
	return mButtons[index] & button && mGamePadInfo[index][button];
}

bool InputGamePad::isButtonUp(const EPlayerIndex& index, const GamePadButton button)
{
	checkButtonInfoRegister(index, button);
	return !(mButtons[index] & button) && mGamePadInfo[index][button];
}

bool InputGamePad::isButtonRelease(const EPlayerIndex& index, const GamePadButton button)
{
	checkButtonInfoRegister(index, button);
	return !(mButtons[index] & button) && !mGamePadInfo[index][button];
}

Vector2 & InputGamePad::getLeftStick(const EPlayerIndex & index)
{
	return mLeftSticks[index];
}

Vector2 & InputGamePad::getRightStick(const EPlayerIndex & index)
{
	return mRightSticks[index];
}

float InputGamePad::getLeftTrigger(const EPlayerIndex & index) const
{
	return (float)GAME_PAD[index].state.Gamepad.bLeftTrigger / TRIGGER_MAX;
}

float InputGamePad::getRightTrigger(const EPlayerIndex & index) const
{
	return (float)GAME_PAD[index].state.Gamepad.bRightTrigger / TRIGGER_MAX;
}

void InputGamePad::checkButtonInfoRegister(const EPlayerIndex& index, const GamePadButton button)
{
	//キー入力情報保管マップにキーが登録されていなければ
	if (mGamePadInfo[index].count(button) == 0)
	{
		//キーは離されている
		mGamePadInfo[index][button] = false;
	}
}

void InputGamePad::checkConnect()
{
	DWORD dwResult;
	for (DWORD i = 0; i < MAX_CONTROLLERS; i++)
	{
		dwResult = XInputGetState(i, &GAME_PAD[i].state);

		if (dwResult == ERROR_SUCCESS)
			GAME_PAD[i].bConnected = true;
		else
			GAME_PAD[i].bConnected = false;
	}
}


/* End of File *****************************************************/