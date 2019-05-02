/**
* @file MathUtility.h
* @brief 数学汎用計算クラスファイル
* @author Ryunosuke Honda.
*/
#pragma once

#include "MathDef.h"
#include <random>

/**
*	数学汎用計算クラス
*/
class MathUtility
{
public:
	static void EulerToQuaternion(Quaternion* q, const float roll, const float yaw, const float pitch)
	{
		float cy = (float)cos(yaw * 0.5);
		float sy = (float)sin(yaw * 0.5);
		float cr = (float)cos(roll * 0.5);
		float sr = (float)sin(roll * 0.5);
		float cp = (float)cos(pitch * 0.5);
		float sp = (float)sin(pitch * 0.5);

		q->w = cy * cr * cp + sy * sr * sp;
		q->x = cy * sr * cp - sy * cr * sp;
		q->y = cy * cr * sp + sy * sr * cp;
		q->z = sy * cr * cp - cy * sr * sp;
	}

	static void EulerToQuaternion(Quaternion* q, const Vector3& euler)
	{
		MathUtility::EulerToQuaternion(q, euler.x, euler.y, euler.z);
	}

	static void RotateVector3(Vector3* pOut, const Quaternion* rot, const Vector3* v)
	{
		Quaternion qv = { v->x, v->y, v->z, 0 };
		Quaternion qcg;
		D3DXQuaternionConjugate(&qcg, rot);
		Quaternion ans = *rot * qv * qcg;
		pOut->x = ans.x; pOut->y = ans.y; pOut->z = ans.z;
	}

	/**
	* @fn
	* 乱数の生成(int型)
	* @brief 引数min,maxの間の乱数を生成する
	* @param (min) 最小値
	* @param (max) 最大値
	* @return min,maxの間の乱数
	*/
	static int randRange(int min, int max)
	{
		///FIXME フィールド化
		// 非決定的な乱数生成器でシード生成器を生成
		std::random_device rnd;
		// メルセンヌ・ツイスタ 引数は初期シード値 ファンクタを渡す
		std::mt19937 mt(rnd());
		// min, max間の一様乱数
		std::uniform_int_distribution<int> randRange(min, max);

		return randRange(mt);
	}

	/**
	* @fn
	* 乱数の生成(float型)
	* @brief 引数min,maxの間の乱数を生成する
	* @param (min) 最小値
	* @param (max) 最大値
	* @return min,maxの間の乱数
	*/
	static float randRange(float min, float max)
	{
		///FIXME フィールド化
		// 非決定的な乱数生成器でシード生成器を生成
		std::random_device rnd;
		// メルセンヌ・ツイスタ 引数は初期シード値 ファンクタを渡す
		std::mt19937 mt(rnd());
		// min, max間の一様乱数
		std::uniform_real_distribution<float> randRange(min, max);

		return randRange(mt);
	}

	/**
	* @fn
	* オイラー角(Vector3)を回転行列(Matrix4x4)から抽出する
	* @param (euler) オイラー角(出力)
	* @param (rot) 回転行列
	*/
	static Vector3 computeEulerAngleFromMatrix(const Vector3& euler, const Matrix4x4 &rot)
	{
		Vector3 out;
		float threshold = 0.001f;

		if (abs(rot.m[2][1] - 1.0f) < threshold) 
		{
			// rot(2,1) = sin(x) = 1の時
			out.x = (float)D3DXToDegree(D3DX_PI / 2.0f);
			out.y = 0;
			out.z = (float)D3DXToDegree(atan2(rot.m[1][0], rot.m[0][0]));
		}
		else if (abs(rot.m[2][1] + 1.0f) < threshold) 
		{
			// rot(2,1) = sin(x) = -1の時
			out.x = (float)D3DXToDegree(-D3DX_PI / 2.0f);
			out.y = 0;
			out.z = (float)D3DXToDegree(atan2(rot.m[1][0], rot.m[0][0]));
		}
		else 
		{
			out.x = (float)D3DXToDegree(asin(rot.m[2][1]));
			out.y = (float)D3DXToDegree(atan2(-rot.m[2][0], rot.m[2][2]));
			out.z = (float)D3DXToDegree(atan2(-rot.m[0][1], rot.m[1][1]));
		}

		return out;
	}
};

/* End of File *****************************************************/