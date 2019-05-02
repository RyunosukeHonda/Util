/**
* @file PlayerAiming.cpp
* @brief プレイヤーエイミング(狙いを定めている)状態クラス実装ファイル
* @author Ryunosuke Honda.
*/
#include "PlayerAiming.h"

#include "IInput.h"
#include "Player.h"
#include <XInput.h>

const float PlayerAiming::MOVE_SPEED = 0.10f;
const float PlayerAiming::CAMERA_ROTATE_SPEED = 0.02f;

PlayerAiming::PlayerAiming(Player* pPlayer) :
	mIsEnd(false),
	mpPlayer(pPlayer),
	mMoveAmount(0, 0),
	mCameraRotateAmount(0, 0)
{
}

PlayerAiming::~PlayerAiming()
{
}

void PlayerAiming::init()
{
	mIsEnd = false;
}

void PlayerAiming::shutdown()
{
}

bool PlayerAiming::isEnd()
{
	return mIsEnd;
}

EPlayerState PlayerAiming::next()
{
	return mNext;
}

void PlayerAiming::update(IInput & input)
{
	mMoveAmount = input.getLeftStick(mpPlayer->Index);
	mCameraRotateAmount = input.getRightStick(mpPlayer->Index);

	if (input.isButtonUp(mpPlayer->Index, XINPUT_GAMEPAD_LEFT_SHOULDER))
	{
		mIsEnd = true;
		mNext = EPlayerState::RUN;
	}
}

void PlayerAiming::fixedUpdate(float dt)
{
	mpPlayer->move(mMoveAmount * MOVE_SPEED);
	mpPlayer->rotateCamera(mCameraRotateAmount * CAMERA_ROTATE_SPEED);
	//!右スティック入力量をモデル回転にも加算しておく
	float toEuler = 2.8f;
	mpPlayer->EulerAngle += { 0, mCameraRotateAmount.x * toEuler, 0 };
}

void PlayerAiming::lateUpdate(IInput & input)
{
}

void PlayerAiming::draw(IRenderer & renderer)
{
}

void PlayerAiming::onCollisionEnter(ACollider * other)
{
}

void PlayerAiming::gameSet()
{
	mIsEnd = true;
	mNext = EPlayerState::GAME_SET;
}

/* End of File *****************************************************/