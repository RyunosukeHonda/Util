/**
* @file InputManager.cpp
* @brief 入力機能管理クラス実装ファイル
* @author Ryunosuke Honda.
*/
#include "InputManager.h"

InputManager::InputManager(const HWND& hwnd)
{
	// 「DirectInput」オブジェクトの作成
	DirectInput8Create(
		GetModuleHandle(NULL),
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(VOID**)&mpDinput,
		NULL
	);

	//機能クラスの生成
	mpKey = new InputKey(mpDinput, hwnd);
	mpMouse = new InputMouse(mpDinput, hwnd);
	mpGamePad = new InputGamePad();
}

InputManager::~InputManager()
{
	delete mpKey;
	delete mpMouse;
	SAFE_RELEASE(mpDinput);
}

void InputManager::update()
{
	mpKey->update();
	mpMouse->update();
	mpGamePad->update();
}

void InputManager::lateUpdate()
{
	mpKey->lateUpdate();
	mpMouse->lateUpdate();
	mpGamePad->lateUpdate();
}

bool InputManager::isKeyDown(KeyCode key)
{
	return mpKey->isKeyDown(key);
}

bool InputManager::isKeyPress(KeyCode key)
{
	return mpKey->isKeyPress(key);
}

bool InputManager::isKeyUp(KeyCode key)
{
	return mpKey->isKeyUp(key);
}

bool InputManager::isKeyRelease(KeyCode key)
{
	return mpKey->isKeyRelease(key);
}

bool InputManager::isMouseButtonDown(EMouseButton mouse)
{
	return mpMouse->isMouseButtonDown(mouse);
}

bool InputManager::isMouseButtonPress(EMouseButton mouse)
{
	return mpMouse->isMouseButtonPress(mouse);
}

bool InputManager::isMouseButtonUp(EMouseButton mouse)
{
	return mpMouse->isMouseButtonUp(mouse);
}

bool InputManager::isMouseButtonRelease(EMouseButton mouse)
{
	return mpMouse->isMouseButtonRelease(mouse);
}

const Vector2 & InputManager::getMousePosition()
{
	return mpMouse->getPos();
}

bool InputManager::isButtonDown(const EPlayerIndex& index, const GamePadButton button)
{
	return mpGamePad->isButtonDown(index, button);
}

bool InputManager::isButtonPress(const EPlayerIndex& index, const GamePadButton button)
{
	return mpGamePad->isButtonPress(index, button);
}

bool InputManager::isButtonUp(const EPlayerIndex& index, const GamePadButton button)
{
	return mpGamePad->isButtonUp(index, button);
}

bool InputManager::isButtonRelease(const EPlayerIndex& index, const GamePadButton button)
{
	return mpGamePad->isButtonRelease(index, button);
}

Vector2 & InputManager::getLeftStick(const EPlayerIndex & index)
{
	return mpGamePad->getLeftStick(index);
}

Vector2 & InputManager::getRightStick(const EPlayerIndex & index)
{
	return mpGamePad->getRightStick(index);
}

float InputManager::getLeftTrigger(const EPlayerIndex & index)
{
	return mpGamePad->getLeftTrigger(index);
}

float InputManager::getRightTrigger(const EPlayerIndex & index)
{
	return mpGamePad->getRightTrigger(index);
}

/* End of File *****************************************************/