/**
* @file RectTransform.cpp
* @brief 2�����g�����X�t�H�[���N���X�����t�@�C��
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
	///�`��D��x���f�v�X�l�������邱�ƂŎ���
	D3DXMatrixTranslation(&trans, mPosition.x, mPosition.y, -mSortingLayer);

	//�����Ɋi�[���ĕԂ�
	*pOut = scale * rot * trans;
}

/* End of File *****************************************************/