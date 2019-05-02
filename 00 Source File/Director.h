/**
* @file Director.h
* @brief エントリーポイントから呼び出され各機能の初期化などを行う
* @author Ryunosuke Honda.
*/
#pragma once

#include "Base.h"
#include "Window.h"
#include "EScene.h"
#include "SceneManager.h"

class IGameDevice;

#define APP_NAME L"game 3D action"

/**
*	ディレクタークラス
*/
class Director : public CElement
{
public:
	/**
	* @fn
	* コンストラクタ
	*/
	Director();

	/**
	* @fn
	* デストラクタ
	*/
	~Director();

	/**
	* @fn
	* 実行メソッド
	* @brief エントリーポイントから呼び出す
	*/
	void Run(HINSTANCE);

private:
	/**
	* @fn
	* 初期化
	*/
	HRESULT Init();

	/**
	* @fn
	* メインループ
	*/
	void MainLoop();

	/**
	* @fn
	* FPS矯正
	*/
	void FixFPS();

private:
	//!フレームレート(定数)
	static const float FRAME_RATE;

	HINSTANCE mInstance;
	//!ウィンドウクラス
	Window mWindow;
	//!ゲームデバイスクラス仲介インターフェース
	IGameDevice* mpGameDevice;
	//!シーン管理クラス・ゲームメイン部分はこちらに任せる
	SceneManager mSceneManager;
};

/****** End of File *****************************************************/