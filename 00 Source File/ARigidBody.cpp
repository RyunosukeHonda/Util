/**
* @file ARigidBody.cpp
* @brief ���̒��ۃN���X�����t�@�C��
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
	//�d�͉��Z����Ȃ�O�͂��d�͉����x�݂̂ɂ���
	if (mUseGravity)
		Force = Vector3(0, -GRAVITY * Mass, 0);

	//�Փ˓_��������
	Pt = LocalPosition;

	//��]�͂̏�����
	Torque = { 0, 0, 0 };
}

void ARigidBody::fixedUpdate(float dt)
{
	//���i�^��(�O�͂������x�ɕς���)
	Acc = mForce / Mass;
	Vel += Acc * dt;
	LocalPosition += Vel * dt;

	if (!mFreezeRotation)
	{
		//��]�^��
		//�p���x�ւƃg���N�������n(���[���h���W)�����]�n(�I�u�W�F�N�g���W�n)�֕ϊ�
		MathUtility::RotateVector3(&mOmegaObj, &mPosture, &mOmega);
		MathUtility::RotateVector3(&mTorqueObj, &mPosture, &mTorque);

		//�p�^���� L = I��
		D3DXVec3TransformCoord(&mAngMomentum, &mOmegaObj, &mInertia);

		//�p�����x�@�� = (Torque - �� �~ (I��)) * I ^ (-1)
		D3DXVec3Cross(&mAlpha, &mOmegaObj, &mAngMomentum);
		D3DXVec3TransformCoord(&mAlpha, &(mTorqueObj - mAlpha), &mInverseInertia);

		//�����n(���[���h���W�ɖ߂�)
		MathUtility::RotateVector3(&mAlpha, &mPosture, &mAlpha);

		//�p���x�����߂�
		Omega += Alpha * dt;

		//��](�p�����x��)���p���ɉ�����
		Quaternion Omega_Q = { Omega.x, Omega.y, Omega.z, 0 };
		mPosture += 0.5f * Omega_Q * mPosture * dt;//Q' = Q + Q*1 / 2��dt
		D3DXQuaternionNormalize(&mPosture, &mPosture);
	}

	init();
}

/* End of File *****************************************************/