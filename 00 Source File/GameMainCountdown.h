/**
* @file GameMainCountdown.h
* @brief ゲームメインシーン状態・カウントダウンクラス定義ファイル
* @author Ryunosuke Honda.
*/
#pragma once

#include "IGameMainState.h"
#include "Timer.h"

#include "UIImageObject.h"
#include <memory>
#include <unordered_map>

/**
*	ゲームメインシーン状態・カウントダウンクラス
*	ゲーム開始までのカウントダウンを行い、その間は操作を受け付けない
*/
class GameMainCountdown : public IGameMainState
{
	///定数
private:
	//!Start!!の画像インデックス
	static const int START = 0;
	//!１の画像インデックス
	static const int ONE = 1;
	//!２の画像インデックス
	static const int TWO = 2;
	//!３の画像インデックス
	static const int THREE = 3;

public:
	/**
	 * @fn
	 * デフォルトコンストラクタ
	 */
	GameMainCountdown();

	/**
	 * @fn
	 * デストラクタ
	 */
	~GameMainCountdown();

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
	//!カウントダウンタイマー
	Timer mTimer;
	//!UI画像ポインタ命名
	using CountImagePointer = std::unique_ptr<UIImageObject>;
	//!時間に対応したUI画像を格納するマップ命名
	using CountImageMap =  std::unordered_map<int, CountImagePointer>;
	//!時間に対応したUI画像を格納するマップ
	CountImageMap mCountImage[GameDef::PLAYER_COUNT];
};

/* End of File *****************************************************/