/**
* @file IInputManager.h
* @brief 入力機能管理クラス定義ファイル
* @author Ryunosuke Honda.
*/
#pragma once

#include "IInput.h"
#include "InputKey.h"
#include "InputMouse.h"
#include "InputGamePad.h"
#include <dinput.h>

#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"dinput8.lib")

/**
*	入力機能クラス
*/
class InputManager : public IInput
{
public:
	/**
	 * @fn
	 * デフォルトコンストラクタ
	 * @brief 生成と同時に各機能の初期化を行います
	 */
	InputManager(const HWND& hwnd);
	
	/**
	 * @fn
	 * デストラクタ
	 */
	~InputManager();

	// IInput を介して継承されました
	virtual void update() override;
	virtual void lateUpdate() override;
	virtual bool isKeyDown(KeyCode key) override;
	virtual bool isKeyPress(KeyCode key) override;
	virtual bool isKeyUp(KeyCode key) override;
	virtual bool isKeyRelease(KeyCode key) override;
	virtual bool isMouseButtonDown(EMouseButton mouse) override;
	virtual bool isMouseButtonPress(EMouseButton mouse) override;
	virtual bool isMouseButtonUp(EMouseButton mouse) override;
	virtual bool isMouseButtonRelease(EMouseButton mouse) override;
	virtual const Vector2 & getMousePosition() override;
	virtual bool isButtonDown(const EPlayerIndex& index, const GamePadButton button) override;
	virtual bool isButtonPress(const EPlayerIndex& index, const GamePadButton button) override;
	virtual bool isButtonUp(const EPlayerIndex& index, const GamePadButton button) override;
	virtual bool isButtonRelease(const EPlayerIndex& index, const GamePadButton button) override;
	virtual Vector2 & getLeftStick(const EPlayerIndex & index) override;
	virtual Vector2 & getRightStick(const EPlayerIndex & index) override;
	virtual float getLeftTrigger(const EPlayerIndex & index) override;
	virtual float getRightTrigger(const EPlayerIndex & index) override;

private:
	//!入力機器
	LPDIRECTINPUT8 mpDinput;
	//!キーボード入力クラス
	InputKey* mpKey;
	//!マウス入力クラス
	InputMouse* mpMouse;
	//!ゲームパッド入力クラス
	InputGamePad* mpGamePad;
};

/* End of File *****************************************************/