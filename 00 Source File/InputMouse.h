/**
* @file InputMouse.h
* @brief マウス入力管理クラス
* @author Ryunosuke Honda.
*/
#pragma once

#include "Base.h"
#include "EMouseButton.h"

#include <dinput.h>
#include <unordered_map>

/**
*	マウス入力クラス
*/
class InputMouse : public CElement
{
public:
	/**
	 * @fn
	 * デフォルトコンストラクタ
	 */
	InputMouse(LPDIRECTINPUT8 pDinput, const HWND& hwnd);

	/**
	 * @fn
	 * デストラクタ
	 */
	~InputMouse();

	/**
	* @fn
	* 入力処理更新
	* @brief 実際に入力を取得する
	*/
	void update();

	/**
	* @fn
	* 入力情報更新
	* @brief 取得した入力情報を次フレームで使用するために保存する処理
	*/
	void lateUpdate();

	/**
	* @fn
	* マウスボタンが押された瞬間を取得
	* @param (mouse) マウスボタン、定義済みの列挙型で指定
	*/
	bool isMouseButtonDown(EMouseButton mouse);

	/**
	* @fn
	* マウスボタンが押されているかを取得
	* @param (mouse) マウスボタン、定義済みの列挙型で指定
	*/
	bool isMouseButtonPress(EMouseButton mouse);

	/**
	* @fn
	* マウスボタンが離された瞬間を取得
	* @param (mouse) マウスボタン、定義済みの列挙型で指定
	*/
	bool isMouseButtonUp(EMouseButton mouse);

	/**
	* @fn
	* マウスボタンが離されているか
	* @param (mouse) マウスボタン、定義済みの列挙型で指定
	*/
	bool isMouseButtonRelease(EMouseButton mouse);

private:
	//!マウス入力機器
	LPDIRECTINPUTDEVICE8 mpMouseDevice;
	//!マウス情報格納マップの命名
	using MouseInfoMap = unordered_map<EMouseButton, bool>;
	//!マウス情報格納マップ
	MouseInfoMap mMouseInfo;
	//!マウス情報取得機器
	DIMOUSESTATE2 dims;

	///以下プロパティ
	//!マウスカーソル移動量
	PROPERTY_READONLY(Vector2, Pos);
};

/* End of File *****************************************************/