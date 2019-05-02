/**
* @file PlayerRun.h
* @brief プレイヤー走行(移動)状態クラス定義ファイル
* @author Ryunosuke Honda.
*/
#pragma once

#include "IPlayerState.h"

class Player;

/**
*	プレイヤー走行(移動)状態クラス
*/
class PlayerRun : public IPlayerState
{
	///定数
private:
	//!移動速度
	static const float MOVE_SPEED;
	//!カメラ回転速度
	static const float CAMERA_ROTATE_SPEED;

public:
	/**
	* @fn
	* コンストラクタ
	* @param (pPlayer) プレイヤーポインタ
	*/
	PlayerRun(Player* pPlayer);

	/**
	 * @fn
	 * デストラクタ
	 */
	~PlayerRun();

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
	//!終了フラグ
	bool mIsEnd;
	//!次の移動先ステート
	EPlayerState mNext;
	//!トランスフォーム情報
	Player* mpPlayer;
	//!移動量保存・入力を受け取るのはupdateだが移動処理自体はfixedUpdateで行うため保存が必要
	Vector2 mMoveAmount;
	//!同じくカメラ回転量保存
	Vector2 mCameraRotateAmount;
};

/* End of File *****************************************************/