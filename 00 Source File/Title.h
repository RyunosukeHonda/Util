/**
* @file Title.h
* @brief タイトルシーン定義ファイル
* @author Ryunosuke Honda.
*/
#pragma once

#include "IScene.h"
#include "ObjectManager.h"
#include "Camera.h"
#include "TitleSequencer.h"

/**
*	タイトルシーン
*/
class Title : public IScene
{
public:
	/**
	* @fn
	* デフォルトコンストラクタ
	*/
	Title();

	/**
	* @fn
	* デストラクタ
	*/
	~Title();

	// IScene を介して継承されました
	virtual void init() override;
	virtual void update(IInput& input) override;
	virtual void fixedUpdate(float dt) override;
	virtual void lateUpdate(IInput& input) override;
	virtual void draw(IRenderer& renderer) override;
	virtual bool isEnd() override;
	virtual void shutdown() override;
	virtual EScene next() override;

private:
	//!描画用オブジェクト管理クラス・キャラクターは使わないのでこちらで十分
	ObjectManager mObjectManager;
	//!カメラ・特に機能は必要なし
	Camera mCamera;
	//!終了フラグ
	bool mIsEnd;
	//!タイトルシーケンサークラス
	TitleSequencer mTitleSequencer;
};

/****** End of File *****************************************************/