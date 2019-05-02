/**
* @file IInput.h
* @brief 入力機器インターフェース
* @author Ryunosuke Honda.
*/
#pragma once

#include "Base.h"
#include <XInput.h>
#include "EMouseButton.h"
#include "EPlayerIndex.h"

using KeyCode = int;
using GamePadButton = unsigned short;

/**
*	入力機器インターフェース
*/
class IInput
{
public:
	/**
	* @fn
	* 更新処理
	* @brief 入力を取得する
	*/
	virtual void update() = 0;

	/**
	* @fn
	* 遅延更新処理
	* @brief 取得した入力情報を次フレームで使用するために保存する
	*/
	virtual void lateUpdate() = 0;


	/**
	* @fn
	* キーが押された瞬間を取得
	* @param (key) キーコード、定義済みの16進数[DIK_]で指定
	*/
	virtual bool isKeyDown(KeyCode key) = 0;

	/**
	* @fn
	* キーが押されているかを取得
	* @param (key) キーコード、定義済みの16進数[DIK_]で指定
	*/
	virtual bool isKeyPress(KeyCode key) = 0;

	/**
	* @fn
	* キーが離された瞬間を取得
	* @param (key) キーコード、定義済みの16進数[DIK_]で指定
	*/
	virtual bool isKeyUp(KeyCode key) = 0;

	/**
	* @fn
	* キーが離されているか
	* @param (key) キーコード、定義済みの16進数[DIK_]で指定
	*/
	virtual bool isKeyRelease(KeyCode key) = 0;

	/**
	* @fn
	* マウスボタンが押された瞬間を取得
	* @param (mouse) マウスボタン、定義済みの列挙型で指定
	*/
	virtual bool isMouseButtonDown(EMouseButton mouse) = 0;

	/**
	* @fn
	* マウスボタンが押されているかを取得
	* @param (mouse) マウスボタン、定義済みの列挙型で指定
	*/
	virtual bool isMouseButtonPress(EMouseButton mouse) = 0;

	/**
	* @fn
	* マウスボタンが離された瞬間を取得
	* @param (mouse) マウスボタン、定義済みの列挙型で指定
	*/
	virtual bool isMouseButtonUp(EMouseButton mouse) = 0;

	/**
	* @fn
	* マウスボタンが離されているか
	* @param (mouse) マウスボタン、定義済みの列挙型で指定
	*/
	virtual bool isMouseButtonRelease(EMouseButton mouse) = 0;

	/**
	* @fn
	* マウスボタンが離されているか
	* @param (mouse) マウスボタン、定義済みの列挙型で指定
	*/
	virtual const Vector2& getMousePosition() = 0;

	/**
	* @fn
	* パッドボタンが押された瞬間を取得
	* @param (button) パッドボタン、定義済みの列挙型で指定
	*/
	virtual bool isButtonDown(const EPlayerIndex& index, const GamePadButton button) = 0;

	/**
	* @fn
	* パッドボタンが押されているかを取得
	* @param (button) パッドボタン、定義済みの列挙型で指定
	*/
	virtual bool isButtonPress(const EPlayerIndex& index, const GamePadButton button) = 0;

	/**
	* @fn
	* パッドボタンが離された瞬間を取得
	* @param (button) パッドボタン、定義済みの列挙型で指定
	*/
	virtual bool isButtonUp(const EPlayerIndex& index, const GamePadButton button) = 0;

	/**
	* @fn
	* パッドボタンが離されているか
	* @param (button) パッドボタン、定義済みの列挙型で指定
	*/
	virtual bool isButtonRelease(const EPlayerIndex& index, const GamePadButton button) = 0;

	/**
	* @fn
	* パッドの左スティックの入力量を取得
	*/
	virtual Vector2& getLeftStick(const EPlayerIndex& index) = 0;

	/**
	* @fn
	* パッドの右スティックの入力量を取得
	*/
	virtual Vector2& getRightStick(const EPlayerIndex& index) = 0;

	/**
	* @fn
	* パッドの左トリガーの入力量を取得
	*/
	virtual float getLeftTrigger(const EPlayerIndex& index) = 0;
	
	/**
	* @fn
	* パッドの左トリガーの入力量を取得
	*/
	virtual float getRightTrigger(const EPlayerIndex& index) = 0;
};

/* End of File *****************************************************/