/**
* @file RectTransform.cpp
* @brief 2次元トランスフォームクラス実装ファイル
* @author Ryunosuke Honda.
*/
#include "RectTransform.h"

RectTransform::RectTransform() :
	mPosition(0, 0),
	mEulerAngle(0, 0, 0),
	mScale(1, 1),
	mSortingLayer(0)
{
}

RectTransform::~RectTransform()
{
}

void RectTransform::makeWorld(Matrix4x4 * pOut)
{
	Matrix4x4 scale;
	Matrix4x4 rot;
	Matrix4x4 trans;
	D3DXMatrixScaling(&scale, mScale.x, mScale.y, 1);
	D3DXMatrixRotationYawPitchRoll(&rot, D3DXToRadian(mEulerAngle.y), D3DXToRadian(mEulerAngle.x), D3DXToRadian(mEulerAngle.z));
	///描画優先度をデプス値をいじることで実現
	D3DXMatrixTranslation(&trans, mPosition.x, mPosition.y, -mSortingLayer);

	//引数に格納して返す
	*pOut = scale * rot * trans;
}

/* End of File *****************************************************/