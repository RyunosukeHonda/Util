/**
* @file PlayerIdle.h
* @brief プレイヤー待機状態クラス定義ファイル
* @author Ryunosuke Honda.
*/
#pragma once

#include "IPlayerState.h"
#include "EPlayerIndex.h"

class Player;

/**
*	プレイヤー待機状態クラス
*	アニメーションを0に戻す
*/
class PlayerIdle : public IPlayerState
{
	///定数
private:
	//!カメラ回転速度
	static const float CAMERA_ROTATE_SPEED;

public:
	/**
	* @fn
	* コンストラクタ
	* @param (pPlayer) プレイヤーポインタ
	*/
	PlayerIdle(Player* pPlayer);

	/**
	 * @fn
	 * デストラクタ
	 */
	~PlayerIdle();

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

private:
	//!終了フラグ
	bool mIsEnd;
	//!次のステート
	EPlayerState mNext;
	//!プレイヤー情報
	Player* mpPlayer;
	//!カメラ回転量保存・入力を受け取るのはupdateだが移動処理自体はfixedUpdateで行うため保存が必要
	Vector2 mCameraRotateAmount;

	// IPlayerState を介して継承されました
	virtual void gameSet() override;
};

/* End of File *****************************************************/