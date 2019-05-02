/**
* @file ARigidBody.cpp
* @brief 剛体抽象クラス実装ファイル
* @author Ryunosuke Honda.
*/
#include "ARigidBody.h"

const float ARigidBody::GRAVITY = 9.8f;

ARigidBody::ARigidBody(const ERigidType& type) :
	base(),
	mType(type),
	mUseGravity(true),
	mFreezeRotation(true),
	mForce(0, 0, 0),
	Acc(0, 0, 0),
	Vel(0, 0, 0),
	mTorque(0, 0, 0),
	mAlpha(0, 0, 0),
	mOmega(0, 0, 0),
	mMass(1.0f),
	mUK(1.0f),
	mUS(1.0f),
	mE(0.0f),
	mPt(0, 0, 0)
{
	init();
}

ARigidBody::~ARigidBody()
{
}

void ARigidBody::addForce(Vector3 & force)
{
	mForce += force;
}

void ARigidBody::init()
{
	//重力加算するなら外力を重力加速度のみにする
	if (mUseGravity)
		Force = Vector3(0, -GRAVITY * Mass, 0);

	//衝突点を初期化
	Pt = LocalPosition;

	//回転力の初期化
	Torque = { 0, 0, 0 };
}

void ARigidBody::fixedUpdate(float dt)
{
	//並進運動(外力を加速度に変える)
	Acc = mForce / Mass;
	Vel += Acc * dt;
	LocalPosition += Vel * dt;

	if (!mFreezeRotation)
	{
		//回転運動
		//角速度ωとトルクを慣性系(ワールド座標)から回転系(オブジェクト座標系)へ変換
		MathUtility::RotateVector3(&mOmegaObj, &mPosture, &mOmega);
		MathUtility::RotateVector3(&mTorqueObj, &mPosture, &mTorque);

		//角運動量 L = Iω
		D3DXVec3TransformCoord(&mAngMomentum, &mOmegaObj, &mInertia);

		//角加速度　α = (Torque - ω × (Iω)) * I ^ (-1)
		D3DXVec3Cross(&mAlpha, &mOmegaObj, &mAngMomentum);
		D3DXVec3TransformCoord(&mAlpha, &(mTorqueObj - mAlpha), &mInverseInertia);

		//慣性系(ワールド座標に戻す)
		MathUtility::RotateVector3(&mAlpha, &mPosture, &mAlpha);

		//角速度を求める
		Omega += Alpha * dt;

		//回転(角加速度分)を姿勢に加える
		Quaternion Omega_Q = { Omega.x, Omega.y, Omega.z, 0 };
		mPosture += 0.5f * Omega_Q * mPosture * dt;//Q' = Q + Q*1 / 2ωdt
		D3DXQuaternionNormalize(&mPosture, &mPosture);
	}

	init();
}

/* End of File *****************************************************/