/**
* @file BattleMode.h
* @brief バトルモードシーンクラス定義ファイル
* @author Ryunosuke Honda.
*/
#pragma once

#include "IScene.h"

#include "ObjectManager.h"
#include "CharacterManager.h"
#include "PlayableCharacterManager.h"
#include "ColliderManager.h"
#include "GameMainSequencer.h"

/**
*	バトルモードシーンクラス
*/
class BattleMode : public IScene
{
public:
	/**
	 * @fn
	 * デフォルトコンストラクタ
	 */
	BattleMode();

	/**
	 * @fn
	 * デストラクタ
	 */
	~BattleMode();

	// IScene を介して継承されました
	virtual void init() override;

	virtual void update(IInput & input) override;

	virtual void fixedUpdate(float dt) override;

	virtual void lateUpdate(IInput & input) override;

	virtual void draw(IRenderer & renderer) override;

	virtual bool isEnd() override;

	virtual void shutdown() override;

	virtual EScene next() override;

private:
	//!更新の必要のないオブジェクトの管理クラス
	ObjectManager mObjManager;
	//!操作キャラクター管理クラス
	PlayableCharacterManager mPlayableCharacterManager;
	//!キャラクター管理クラス
	CharacterManager mCharacterManager;
	//!コライダー管理クラス
	ColliderManager mColliderManager;
	//!ゲームメインシーンシーケンサークラス
	GameMainSequencer mSequencer;
	//!シーン終了フラグ
	bool mIsEnd;
};

/* End of File *****************************************************/