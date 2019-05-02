/**
* @file ARigidBody.h
* @brief 剛体抽象クラス定義ファイル
* @author Ryunosuke Honda.
*/
#pragma once

#include "Transform.h"
#include "ERigidType.h"

/**
*	剛体抽象クラス・コライダーに継承させて物理挙動を行います
*/
class ARigidBody : public Transform
{
public:
	/**
	* @fn
	* コンストラクタ
	* @param (type) 剛体の形状を指定
	*/
	ARigidBody(const ERigidType& type);

	/**
	 * @fn
	 * 仮想デストラクタ
	 */
	virtual ~ARigidBody();

	void addForce(Vector3& force);

protected:
	/**
	* @fn
	* FPS矯正更新・物理挙動の計算を行う
	* @param (dt) フレーム偏差時間
	*/
	void fixedUpdate(float dt);

private:
	/**
	* @fn
	* 初期化
	*/
	void init();

protected:
	//!重力・定数
	static const float GRAVITY;
	//!形状・プロパティでGetterのみ公開
	PROPERTY_READONLY(ERigidType, Type);
	//!重力を加算するかどうか
	PROPERTY_READWRITE(bool, UseGravity);
	//!回転を固定するかどうか
	PROPERTY_READWRITE(bool, FreezeRotation);
	//!外力(N)
	PROPERTY_READWRITE(Vector3, Force);
	//!加速度(m/ss)
	Vector3 Acc;
	//!速度(m/s)     
	Vector3 Vel;
	//トルク(N・m)
	PROPERTY_READWRITE(Vector3, Torque);
	//角加速度a(rad/ss)
	PROPERTY_READWRITE(Vector3, Alpha);
	//角速度ω(rad/s)
	PROPERTY_READWRITE(Vector3, Omega);
	//!質量(kg)
	PROPERTY_READWRITE(float, Mass);
	//!動摩擦係数
	PROPERTY_READWRITE(float, UK);
	//!静止摩擦係数
	PROPERTY_READWRITE(float, US);
	//!反発係数
	PROPERTY_READWRITE(float, E);
	//!衝突点
	PROPERTY_READWRITE(Vector3, Pt);

private:
	//!基底クラス命名
	using base = Transform;
	//角運動量
	Vector3 mAngMomentum;
	//オブジェクト座標系のω
	Vector3 mOmegaObj;
	//オブジェクト座標のトルク
	Vector3 mTorqueObj;
	//回転姿勢
	Quaternion mPosture;
	//慣性モーメント
	Matrix4x4 mInertia;
	//慣性モーメントの逆行列
	Matrix4x4 mInverseInertia;
};

/* End of File *****************************************************/