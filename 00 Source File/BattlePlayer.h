///**
//* @file BattlePlayer.h
//* @brief 対戦モード用プレイヤークラス定義ファイル
//* Playerクラスを基底とし、多人数プレイの入力・描画に対応させたクラス
//* @author Ryunosuke Honda.
//*/
//#pragma once
//
//#include "Player.h"
//#include "EPlayerIndex.h"
//
///**
//*	対戦モード用プレイヤークラス
//*/
//class BattlePlayer : public Player
//{
//public:
//	/**
//	* @fn
//	* コンストラクタ
//	* @param (index) プレイヤー番号
//	* @param (hp) 体力
//	*/
//	BattlePlayer(EPlayerIndex index, int hp, IAddable<ACharacter>* characterMgr, IAddable<ACollider>* colliderMgr);
//
//	/**
//	 * @fn
//	 * デストラクタ
//	 */
//	~BattlePlayer();
//
//	virtual void init() override;
//
//	virtual void update(IInput& input) override;
//
//	virtual void onCollisionEnter(ACollider* other)override;
//
//private:
//	using base = Player;
//	//!プレイヤー番号
//	EPlayerIndex mIndex;
//};
//
///* End of File *****************************************************/