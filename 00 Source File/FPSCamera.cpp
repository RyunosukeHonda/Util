/**
* @file FPSCamera.cpp
* @brief FPS�J�����N���X�����t�@�C��
* @author Ryunosuke Honda.
*/
#include "FPSCamera.h"

FPSCamera::FPSCamera(Transform * follow) :
	mpObject(follow),
	mRotateAmount(0, 0),
	mOffset(0, 0, 0)
{
}

FPSCamera::~FPSCamera()
{
}

void FPSCamera::init(const Vector2& initRotateAmount)
{
	mRotateAmount = initRotateAmount;
}

void FPSCamera::update()
{
	//�J�����ʒu�ݒ�E�^�[�Q�b�g�ɍ��������Z�����l
	mPosition = mpObject->Position + mOffset;
	//�����Ă���������Z�o���A�O�������x�N�g���Ƃ��Ċi�[
	D3DXVec3Normalize(&mForward, &(mLookPt - mPosition));
	//�����_�X�V
	mLookPt =
	{
		mPosition.x + (float)sin(mRotateAmount.x),
		mRotateAmount.y,
		mPosition.z + (float)cos(mRotateAmount.x)
	};
	//�e�s��̌v�Z
	calcViewProj();
}

/* End of File *****************************************************/