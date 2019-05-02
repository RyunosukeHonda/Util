/**
* @file InputKey.h
* @brief キー入力検知クラス定義ファイル
* @author Ryunosuke Honda.
*/
#pragma once

#include "Base.h"

#include <dinput.h>
#include <unordered_map>

/**
*	キー入力検知クラス
*/
class InputKey : public CElement
{
	///定数定義
public:
	//!キー番号命名
	using KeyCode = int;

public:
	/**
	 * @fn
	 * デフォルトコンストラクタ
	 */
	InputKey(LPDIRECTINPUT8 pDinput, const HWND& hwnd);

	/**
	 * @fn
	 * デストラクタ
	 */
	~InputKey();

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
	* キーが押された瞬間を取得
	* @param (key) キーコード、定義済みの16進数[DIK_]で指定
	*/
	bool isKeyDown(KeyCode key);

	/**
	* @fn
	* キーが押されているかを取得
	* @param (key) キーコード、定義済みの16進数[DIK_]で指定
	*/
	bool isKeyPress(KeyCode key);

	/**
	* @fn
	* キーが離された瞬間を取得
	* @param (key) キーコード、定義済みの16進数[DIK_]で指定
	*/
	bool isKeyUp(KeyCode key);

	/**
	* @fn
	* キーが離されているか
	* @param (key) キーコード、定義済みの16進数[DIK_]で指定
	*/
	bool isKeyRelease(KeyCode key);

private:
	/**
	* @fn
	* キー情報が登録されているか確認、されていなければ登録
	* @param (key) キーコード
	*/
	void checkKeyInfoRegister(KeyCode key);

private:
	//!キー情報格納用配列
	BYTE diks[256];
	//!キー入力機器
	LPDIRECTINPUTDEVICE8 mpKeyDevice;
	//!キー情報格納マップの命名
	using KeyInfoMap = unordered_map<KeyCode, bool>;
	//!キー情報格納マップ
	KeyInfoMap mKeyInfo;
};

/* End of File *****************************************************/