/**
* @file Camera.cpp
* @brief 抽象カメラクラス実装ファイル
* @author Ryunosuke Honda.
*/
#include "Camera.h"
#include "Screen.h"

Camera::Camera() :
	base(),
	mLookPt(0, 0, -1),
	mUpVec(0, 1, 0),
	mView(),
	mProj(),
	mCullingLayer(0)
{
}

void Camera::update()
{
	calcViewProj();
}

bool Camera::isCulling(const ELayer & layer) const
{
	return ((1 << (unsigned int)layer) & mCullingLayer) != 0;
}

unsigned int Camera::calcLayerMask(const ELayer & layer)
{
	return 1 << (unsigned int)layer;
}

void Camera::calcViewProj()
{
	// ビュー
	D3DXMatrixLookAtLH(&mView, &mPosition, &mLookPt, &mUpVec);

	// プロジェクション
	D3DXMatrixPerspectiveFovLH(&mProj, Screen::FOV, Screen::WINDOW_WIDTH / (Screen::WINDOW_HEIGHT / 2.0f), Screen::NEAR_, Screen::FAR_);
}

/* End of File *****************************************************/