/**
* @file FPSCamera.cpp
* @brief FPSカメラクラス実装ファイル
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
	//カメラ位置設定・ターゲットに差分を加算した値
	mPosition = mpObject->Position + mOffset;
	//向いている方向を算出し、前方方向ベクトルとして格納
	D3DXVec3Normalize(&mForward, &(mLookPt - mPosition));
	//注視点更新
	mLookPt =
	{
		mPosition.x + (float)sin(mRotateAmount.x),
		mRotateAmount.y,
		mPosition.z + (float)cos(mRotateAmount.x)
	};
	//各行列の計算
	calcViewProj();
}

/* End of File *****************************************************/