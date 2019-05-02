/**
* @file PlayerGameSet.h
* @brief プレイヤー決着状態クラス定義ファイル
* @author Ryunosuke Honda.
*/
#pragma once

#include "IPlayerState.h"
#include "EPlayerIndex.h"
#include "UIAppearingImage.h"

class Player;

/**
*	プレイヤー決着状態クラス
*	決着後の演出用
*/
class PlayerGameSet : public IPlayerState
{
public:
	/**
	* @fn
	* コンストラクタ
	* @param (pPlayer) プレイヤーポインタ
	*/
	PlayerGameSet(Player* pPlayer);

	/**
	 * @fn
	 * デストラクタ
	 */
	~PlayerGameSet();

	// IPlayerState を介して継承されました
	virtual void init() override;
	virtual void shutdown() override;
	virtual bool isEnd() override;
	virtual EPlayerState next() override;
	virtual void update(IInput & input) override;
	virtual void fixedUpdate(float dt) override;
	virtual void lateUpdate(IInput & input) override;
	virtual void draw(IRenderer & renderer) override;
	virtual void onCollisionEnter(ACollider * other) override;
	virtual void gameSet() override;

private:
	//!プレイヤー情報
	Player* mpPlayer;
	//!徐々に現れる画像エフェクト
	UIAppearingImage mResultImage;
};

/* End of File *****************************************************/