///**
//* @file PlayerJump.cpp
//* @brief プレイヤージャンプ状態クラス実装ファイル
//* @author Ryunosuke Honda.
//*/
//#include "PlayerJump.h"
//
//#include "Player.h"
//#include "IInput.h"
//
//const float PlayerJump::MOVE_SPEED = 0.1f;
//
//PlayerJump::PlayerJump(Player* pPlayer):
//	mIsEnd(false),
//	mpPlayer(pPlayer),
//	mMoveAmount()
//{
//}
//
//PlayerJump::~PlayerJump()
//{
//}
//
//void PlayerJump::init()
//{
//	mIsEnd = false;
//}
//
//void PlayerJump::shutdown()
//{
//}
//
//bool PlayerJump::isEnd()
//{
//	return mIsEnd;
//}
//
//EPlayerState PlayerJump::next()
//{
//	return EPlayerState::IDLE;
//}
//
//void PlayerJump::update(IInput & input)
//{
//	mMoveAmount = input.getLeftStick(mpPlayer->Index);
//}
//
//void PlayerJump::fixedUpdate(float dt)
//{
//	mpPlayer->move(mMoveAmount * MOVE_SPEED);
//}
//
//void PlayerJump::lateUpdate(IInput & input)
//{
//}
//
//void PlayerJump::draw(IRenderer & renderer)
//{
//}
//
//void PlayerJump::onCollisionEnter(ACollider * other)
//{
//	if (other->Tag == ETag::GROUND)
//	{
//		mIsEnd = true;
//	}
//}
//
///* End of File *****************************************************/