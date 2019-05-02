/**
* @file GameMainBattle.h
* @brief ゲームメインシーン状態・バトルクラス定義ファイル
* @author Ryunosuke Honda.
*/
#pragma once

#include "IGameMainState.h"
#include "ObjectManager.h"

class PlayableCharacterManager;

/**
*	ゲームメインシーン状態・バトルクラス
*	バトルを行わせる、事実上のメインシーン
*/
class GameMainBattle : public IGameMainState
{
public:
	/**
	 * @fn
	 * コンストラクタ
	 */
	GameMainBattle(PlayableCharacterManager* pcManager);

	/**
	 * @fn
	 * デストラクタ
	 */
	~GameMainBattle();

	// IGameMainState を介して継承されました
	virtual void init() override;
	virtual void shutdown() override;
	virtual bool isEnd() override;
	virtual EGameMainState next() override;
	virtual void update(IInput & input) override;
	virtual void fixedUpdate(float dt) override;
	virtual void lateUpdate(IInput & input) override;
	virtual void draw(IRenderer & renderer) override;

private:
	//!プレイヤー管理クラス・既に上位で生成したものを使用するためポインタ変数で保持
	PlayableCharacterManager* mpPlayableCharacterManager;
	//!更新の必要のないオブジェクトの管理クラス・UIなどの描画用
	ObjectManager mObjManager;
};

/* End of File *****************************************************/