/**
* @file Transform.cpp
* @brief オブジェクトの位置、回転、スケールを扱うクラスの実装ファイル
* @author Ryunosuke Honda.
*/
#include "Transform.h"
#include <Windows.h>
#include <DirectXMath.h>
#include "EntityVisitorMemFun1.h"
using namespace DirectX;

Transform::Transform() :
	mLocalPosition(0, 0, 0),
	mLocalEulerAngle(0, 0, 0),
	mLocalScale(1, 1, 1),
	mPosition(0, 0, 0),
	mEulerAngle(0, 0, 0),
	mScale(1, 1, 1),
	mRotation(),
	mRight(1, 0, 0),
	mUp(0, 1, 0),
	mForward(0, 0, 1),
	mTag(ETag::NONE),
	mLayer(ELayer::DEFAULT),
	mParent(nullptr),
	mChildren()
{
}

Transform::~Transform()
{
}

void Transform::makeWorld(Matrix4x4 * world)
{
	Matrix4x4 scale;
	Matrix4x4 rot;
	Matrix4x4 trans;
	D3DXMatrixScaling(&scale, mScale.x, mScale.y, mScale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, D3DXToRadian(mEulerAngle.y), D3DXToRadian(mEulerAngle.x), D3DXToRadian(mEulerAngle.z));
	D3DXMatrixTranslation(&trans, mPosition.x, mPosition.y, mPosition.z);

	//引数に格納して返す
	*world = scale * rot * trans;
}

void Transform::setParent(Transform * parent)
{
	parent->mChildren.add(this);
	mParent = parent;
}

Transform * Transform::getParent()
{
	return mParent;
}

//Transform * Transform::getChild(int index)
//{
//	return mChildren[index];
//}

Transform * Transform::getRoot()
{
	//再起して親オブジェクトを辿っていきなくなれば自身を返す
	if (isRoot())
	{
		return this;
	}

	return mParent->getRoot();
}

bool Transform::isRoot()
{
	return mParent == nullptr;
}

void Transform::lookAt(const Vector3 & target)
{
	/*
	D3DXVECTOR3 X, Y, Z;
	Vector3 U = { 0, 1, 0 };
	Z = target - mPosition;
	D3DXVec3Normalize(&Z, &Z);
	D3DXVec3Cross(&X, D3DXVec3Normalize(&Y, &U), &Z);
	D3DXVec3Normalize(&X, &X);
	D3DXVec3Normalize(&Y, D3DXVec3Cross(&Y, &Z, &X));
	/*/
	D3DXVECTOR3 X, Y, Z, D;
	Vector3 U = { 0, 1, 0 };
	D = target - mPosition;
	D3DXVec3Normalize(&D, &D);
	D3DXVec3Cross(&X, D3DXVec3Normalize(&Y, &U), &D);
	D3DXVec3Normalize(&X, &X);
	D3DXVec3Normalize(&Z, D3DXVec3Cross(&Z, &X, &Y));
	//*/

	Matrix4x4 rot =
	{
		X.x, X.y, X.z, 0,
		Y.x, Y.y, Y.z, 0,
		Z.x, Z.y, Z.z, 0,
		0, 0, 0, 1
	};

	mRotation *= rot;

	MathUtility::computeEulerAngleFromMatrix(EulerAngle, mRotation);

	//Vector3 v = 
	//{
	//	(float)D3DXToRadian(EulerAngle.x),
	//	(float)D3DXToRadian(EulerAngle.y),
	//	(float)D3DXToRadian(EulerAngle.z)
	//};
	//D3DXVec3TransformCoord(&v, &Vector3(0, 0, 1), &rot);

	//EulerAngle =
	//{
	//	0,//(float)D3DXToDegree(v.x),
	//	min((float)D3DXToDegree(v.x),(float)D3DXToDegree(v.z)),
	//	0//(float)D3DXToDegree(v.z)
	//};

}

void Transform::setChild(Transform * child)
{
	mChildren.add(child);
	child->mParent = this;
}

void Transform::calcLocalPosition(const Vector3& position)
{
	if (isRoot()) {
	mPosition = position;
		mLocalPosition = mPosition;
		EntityVisitorMemFun1<Transform, const Vector3&, &Transform::calcLocalPosition> calc(mPosition);
		mChildren.accept(calc);
		return;
	}
	mLocalPosition = mPosition - mParent->mPosition;

	EntityVisitorMemFun1<Transform, const Vector3&, &Transform::calcLocalPosition> calc(mPosition);
	mChildren.accept(calc);
}

void Transform::calcPosition(const Vector3& localPosition)
{
	if (isRoot()) {
		mLocalPosition = localPosition;
		mPosition = mLocalPosition;
		EntityVisitorMemFun1<Transform, const Vector3&, &Transform::calcPosition> calc(mLocalPosition);
		mChildren.accept(calc);
		return;
	}
	mPosition = mParent->mPosition + mLocalPosition;

	EntityVisitorMemFun1<Transform, const Vector3&, &Transform::calcPosition> calc(mLocalPosition);
	mChildren.accept(calc);
}

void Transform::calcLocalEulerAngle(const Vector3 & euler)
{
	if (isRoot()) {
	mEulerAngle = euler;
		mLocalEulerAngle = mEulerAngle;
		calcRotation();
		EntityVisitorMemFun1<Transform, const Vector3&, &Transform::calcLocalEulerAngle> calc(mEulerAngle);
		mChildren.accept(calc);
		return;
	}
	mLocalEulerAngle = mEulerAngle - mParent->mEulerAngle;
	calcRotation();

	EntityVisitorMemFun1<Transform, const Vector3&, &Transform::calcLocalEulerAngle> calc(mEulerAngle);
	mChildren.accept(calc);
}

void Transform::calcEulerAngle(const Vector3& localEuler)
{
	if (isRoot()) {
	mLocalEulerAngle = localEuler;
		mEulerAngle = mLocalEulerAngle;
		calcRotation();
		EntityVisitorMemFun1<Transform, const Vector3&, &Transform::calcEulerAngle> calc(mLocalEulerAngle);
		mChildren.accept(calc);
		return;
	}
	mEulerAngle = mParent->mEulerAngle + mLocalEulerAngle;
	calcRotation();

	EntityVisitorMemFun1<Transform, const Vector3&, &Transform::calcEulerAngle> calc(mLocalEulerAngle);
	mChildren.accept(calc);
}

void Transform::calcLocalScale(const Vector3 & scale)
{
	mScale = scale;
	if (isRoot()) {
		mLocalScale = mScale;
		return;
	}
	mLocalScale = { mScale.x * mParent->mScale.x, mScale.y * mParent->mScale.y, mScale.z * mParent->mScale.z };
}

void Transform::calcScale(const Vector3 & localScale)
{
	mLocalScale = localScale;
	if (isRoot()) {
		mScale = mLocalScale;
		return;
	}
	mScale = { mLocalScale.x * mParent->mScale.x, mLocalScale.y * mParent->mScale.y, mLocalScale.z * mParent->mScale.z };
}

void Transform::calcRotation()
{
	D3DXMatrixRotationYawPitchRoll(&mRotation, D3DXToRadian(LocalEulerAngle.y), D3DXToRadian(LocalEulerAngle.x), D3DXToRadian(LocalEulerAngle.z));
	calcDirection();
}

void Transform::calcDirection()
{
	//ｚ方向ベクトル設定
	Vector3 v(0, 0, 1);
	D3DXVec3TransformCoord(&mForward, &v, &mRotation);
	D3DXVec3Normalize(&mForward, &mForward);

	//x方向ベクトル設定
	v = { 1, 0, 0 };
	D3DXVec3TransformCoord(&mRight, &v, &mRotation);
	D3DXVec3Normalize(&mRight, &mRight);

	//y方向ベクトルは外積で設定
	D3DXVec3Cross(&mUp, &mForward, &mRight);
	D3DXVec3Normalize(&mUp, &mUp);
}

void Transform::updateChildren()
{

}

/* End of File *****************************************************/