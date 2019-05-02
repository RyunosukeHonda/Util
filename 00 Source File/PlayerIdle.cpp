/**
* @file PlayerIdle.cpp
* @brief プレイヤー待機状態クラス実装ファイル
* @author Ryunosuke Honda.
*/
#include "PlayerIdle.h"

#include "Player.h"
#include "FBXSkinMeshRenderDesc.h"
#include "IRenderer.h"
#include "IInput.h"
#include <XInput.h>

const float PlayerIdle::CAMERA_ROTATE_SPEED = 0.05f;

PlayerIdle::PlayerIdle(Player* pPlayer) :
	mIsEnd(false),
	mpPlayer(pPlayer),
	mCameraRotateAmount(0, 0)
{
}

PlayerIdle::~PlayerIdle()
{
}

void PlayerIdle::init()
{
	mIsEnd = false;
	mCameraRotateAmount = { 0,0 };
}

void PlayerIdle::shutdown()
{
}

bool PlayerIdle::isEnd()
{
	return mIsEnd;
}

EPlayerState PlayerIdle::next()
{
	return mNext;
}

void PlayerIdle::update(IInput & input)
{
	mCameraRotateAmount = input.getRightStick(mpPlayer->Index);

	mpPlayer->Frame = 0;

	if (abs(input.getLeftStick(mpPlayer->Index).x) > 0.1f ||
		abs(input.getLeftStick(mpPlayer->Index).y) > 0.1f)
	{
		mNext = EPlayerState::RUN;
		mIsEnd = true;
	}

	if (input.isButtonDown(mpPlayer->Index, XINPUT_GAMEPAD_LEFT_SHOULDER))
	{
		mIsEnd = true;
		mNext = EPlayerState::AIMING;
	}
}

void PlayerIdle::fixedUpdate(float dt)
{
	mpPlayer->rotateCamera(mCameraRotateAmount * CAMERA_ROTATE_SPEED);
	//!右スティック入力量をモデル回転にも加算しておく
	float toEuler = 2.8f;
	mpPlayer->EulerAngle += { 0, mCameraRotateAmount.x * toEuler, 0 };
}

void PlayerIdle::lateUpdate(IInput & input)
{
}

void PlayerIdle::draw(IRenderer & renderer)
{
}

void PlayerIdle::onCollisionEnter(ACollider * other)
{
}

void PlayerIdle::gameSet()
{
	mNext = EPlayerState::GAME_SET;
	mIsEnd = true;
}

/* End of File *****************************************************/