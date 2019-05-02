/**
* @file InputGamePad.h
* @brief ゲームパッド入力機能クラス定義ファイル
* @author Ryunosuke Honda.
*/
#pragma once

#include "Base.h"
#include <vector>
#include <unordered_map>
#include <XInput.h>
#include "EPlayerIndex.h"

#pragma comment(lib,"xinput.lib ")

using GamePadButton = unsigned short;

struct CONTROLER_STATE
{
	XINPUT_STATE state;
	bool bConnected;
};

/**
*	ゲームパッド入力機能クラス
*/
class InputGamePad
{
private:
	//!コントローラー接続最大数
	static const int MAX_CONTROLLERS = 4;  //XInputが認識できるのは4つまで
	//!スティックの取る値の最大値
	static const float STICK_MAX;
	//!トリガーの取る最大値
	static const float TRIGGER_MAX;
public:
	/**
	 * @fn
	 * デフォルトコンストラクタ
	 */
	InputGamePad();

	/**
	 * @fn
	 * デストラクタ
	 */
	~InputGamePad();

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
	* パッドボタンが押された瞬間を取得
	* @param (button) パッドボタン、定義済みの列挙型で指定
	*/
	bool isButtonDown(const EPlayerIndex& index, const GamePadButton button);

	/**
	* @fn
	* パッドボタンが押されているかを取得
	* @param (button) パッドボタン、定義済みの列挙型で指定
	*/
	bool isButtonPress(const EPlayerIndex& index, const GamePadButton button);

	/**
	* @fn
	* パッドボタンが離された瞬間を取得
	* @param (button) パッドボタン、定義済みの列挙型で指定
	*/
	bool isButtonUp(const EPlayerIndex& index, const GamePadButton button);

	/**
	* @fn
	* パッドボタンが離されているか
	* @param (button) パッドボタン、定義済みの列挙型で指定
	*/
	bool isButtonRelease(const EPlayerIndex& index, const GamePadButton button);

	Vector2 & getLeftStick(const EPlayerIndex& index);

	Vector2 & getRightStick(const EPlayerIndex& index);

	float getLeftTrigger(const EPlayerIndex& index) const;

	float getRightTrigger(const EPlayerIndex& index) const;

private:
	/**
	* @fn
	* ボタン入力情報が登録されているか確認、されていなければ登録
	* @param (button) パッドボタン
	*/
	void checkButtonInfoRegister(const EPlayerIndex& index, const GamePadButton button);

	/**
	* @fn
	* コントローラー接続確認
	*/
	void checkConnect();

private:
	//!ゲームパッド情報配列
	CONTROLER_STATE GAME_PAD[MAX_CONTROLLERS];
	//!ボタン入力情報配列
	vector<WORD> mButtons;
	///ゲームパッド情報保管マップ命名
	using GamePadInfoMap = unordered_map<GamePadButton, bool>;
	//!ゲームパッド情報配列
	vector<GamePadInfoMap> mGamePadInfo;
	//!左スティック情報
	vector<Vector2> mLeftSticks;
	//!右スティック情報
	vector<Vector2> mRightSticks;
};

/* End of File *****************************************************/