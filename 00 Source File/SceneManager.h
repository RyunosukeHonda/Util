/**
* @file SceneManager.h
* @brief シーン管理クラス定義ファイル
* @author Ryunosuke Honda.
*/
#pragma once

#include "EScene.h"
#include "IScene.h"
#include "Base.h"
#include "StateMachineTemplate.h"

/**
*	シーン管理クラス
*/
class SceneManager : public StateMachineTemplate<EScene, IScene>
{
public:
	/*
	* @fn
	* デフォルトコンストラクタ
	*/
	SceneManager();

	/*
	* @fn
	* デストラクタ
	*/
	~SceneManager() = default;

	/*
	* @fn
	* シーン更新
	* @param (input) 入力機能
	* @brief 現在実行中のシーンを更新
	*/
	void update(IInput& input);

	/*
	* @fn
	* シーン更新・FPS60に矯正された処理
	* @param (dt)  フレームの差分時間
	* @brief 主に物理周りの処理をこちらで行う
	*/
	void fixedUpdate(float dt);

	/*
	* @fn
	* シーン遅延更新
	* @param (input) 入力機能
	* @brief 他の更新処理が終了した後に処理される更新処理
	* シーン遷移や入力情報保管などを行う
	*/
	void lateUpdate(IInput& input);

	/*
	* @fn
	* シーン描画
	* @param (renderer)  描画オブジェクト
	* @brief 現在実行中のシーンを描画
	*/
	void draw(IRenderer& renderer);

private:
	/*
	* @fn
	* コピーコンストラクタ（コピー禁止）
	* @brief 特殊関数の暗黙定義を明示的に禁止
	*/
	SceneManager(const SceneManager&) = delete;
	SceneManager& operator=(const SceneManager&) = delete;
};

/****** EOF *****************************************************/
