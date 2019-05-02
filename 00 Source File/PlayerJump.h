///**
//* @file PlayerJump.h
//* @brief プレイヤージャンプ状態クラス定義ファイル
//* @author Ryunosuke Honda.
//*/
//#pragma once
//
//#include "IPlayerState.h"
//
//class Player;
//
///**
//*	プレイヤージャンプ状態クラス
//*/
//class PlayerJump : public IPlayerState
//{
//	///定数
//private:
//	//!移動速度
//	static const float MOVE_SPEED;
//
//public:
//	/**
//	 * @fn
//	 * デフォルトコンストラクタ
//	 */
//	PlayerJump(Player* pPlayer);
//
//	/**
//	 * @fn
//	 * デストラクタ
//	 */
//	~PlayerJump();
//
//	// IPlayerState を介して継承されました
//	virtual void init() override;
//	virtual void shutdown() override;
//	virtual bool isEnd() override;
//	virtual EPlayerState next() override;
//	virtual void update(IInput & input) override;
//	virtual void fixedUpdate(float dt) override;
//	virtual void lateUpdate(IInput & input) override;
//	virtual void draw(IRenderer & renderer) override;
//	virtual void onCollisionEnter(ACollider * other) override;
//
//private:
//	//!終了フラグ
//	bool mIsEnd;
//	//!トランスフォーム情報
//	Player* mpPlayer;
//	//!移動量保存・入力を受け取るのはupdateだが移動処理自体はfixedUpdate(float dt)で行うため保存が必要
//	Vector2 mMoveAmount;
//};
//
///* End of File *****************************************************/