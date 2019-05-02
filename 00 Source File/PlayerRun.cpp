/**
* @file PlayerRun.cpp
* @brief プレイヤー走行(移動)状態クラス実装ファイル
* @author Ryunosuke Honda.
*/
#include "PlayerRun.h"

#include "Player.h"
#include "FBXSkinMeshRenderDesc.h"
#include "IRenderer.h"
#include "IInput.h"

const float PlayerRun::MOVE_SPEED = 0.15f;
const float PlayerRun::CAMERA_ROTATE_SPEED = 0.05f;

PlayerRun::PlayerRun(Player* pPlayer) :
	mIsEnd(false),
	mpPlayer(pPlayer),
	mMoveAmount(0, 0),
	mCameraRotateAmount(0, 0)
{
}

PlayerRun::~PlayerRun()
{
}

void PlayerRun::init()
{
	mIsEnd = false;
	mMoveAmount = { 0, 0 };
	mCameraRotateAmount = { 0,0 };
}

void PlayerRun::shutdown()
{
}

bool PlayerRun::isEnd()
{
	return mIsEnd;
}

EPlayerState PlayerRun::next()
{
	return mNext;
}

void PlayerRun::update(IInput & input)
{
	mMoveAmount = input.getLeftStick(mpPlayer->Index);
	mCameraRotateAmount = input.getRightStick(mpPlayer->Index);

	if (abs(input.getLeftStick(mpPlayer->Index).x) < 0.1f &&
		abs(input.getLeftStick(mpPlayer->Index).y) < 0.1f)
	{
		mNext = EPlayerState::IDLE;
		mIsEnd = true;
	}

	if (input.isButtonDown(mpPlayer->Index, XINPUT_GAMEPAD_LEFT_SHOULDER))
	{
		mIsEnd = true;
		mNext = EPlayerState::AIMING;
	}
}

void PlayerRun::fixedUpdate(float dt)
{
	mpPlayer->move(mMoveAmount * MOVE_SPEED);
	mpPlayer->rotateCamera(mCameraRotateAmount * CAMERA_ROTATE_SPEED);
	//!右スティック入力量をモデル回転にも加算しておく
	float toEuler = 2.8f;
	mpPlayer->EulerAngle += { 0, mCameraRotateAmount.x * toEuler, 0 };
}

void PlayerRun::lateUpdate(IInput & input)
{
}

void PlayerRun::draw(IRenderer & renderer)
{
}

void PlayerRun::onCollisionEnter(ACollider * other)
{
}

void PlayerRun::gameSet()
{
	mIsEnd = true;
	mNext = EPlayerState::GAME_SET;
}

/* End of File *****************************************************/