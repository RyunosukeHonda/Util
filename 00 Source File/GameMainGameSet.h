/**
* @file GameMainGameSet.h
* @brief ゲームメインシーン状態・決着クラス定義ファイル
* @author Ryunosuke Honda.
*/
#pragma once

#include "IGameMainState.h"
#include "Timer.h"
#include <functional>

class PlayableCharacterManager;

/**
*	ゲームメインシーン状態・決着クラス
*	決着演出後、タイトル画面に戻る
*/
class GameMainGameSet : public IGameMainState
{
public:
	/**
	 * @fn
	 * コンストラクタ
	 */
	GameMainGameSet(PlayableCharacterManager* pcManager, std::function<void()> endFunc);
	
	/**
	 * @fn
	 * デストラクタ
	 */
	~GameMainGameSet();

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
	//!ゲーム終了を通知する関数
	std::function<void()> mEndFunc;
	//!終了までの時間間隔用タイマー
	Timer mTimer;
	//!プレイヤー管理クラス・既に上位で生成したものを使用するためポインタ変数で保持
	PlayableCharacterManager* mpPlayableCharacterManager;
};

/* End of File *****************************************************/