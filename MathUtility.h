/**
* @file MathUtility.h
* @brief ���w�ėp�v�Z�N���X�t�@�C��
* @author Ryunosuke Honda.
*/
#pragma once

#include "MathDef.h"
#include <random>

/**
*	���w�ėp�v�Z�N���X
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
	* �����̐���(int�^)
	* @brief ����min,max�̊Ԃ̗����𐶐�����
	* @param (min) �ŏ��l
	* @param (max) �ő�l
	* @return min,max�̊Ԃ̗���
	*/
	static int randRange(int min, int max)
	{
		///FIXME �t�B�[���h��
		// �񌈒�I�ȗ���������ŃV�[�h������𐶐�
		std::random_device rnd;
		// �����Z���k�E�c�C�X�^ �����͏����V�[�h�l �t�@���N�^��n��
		std::mt19937 mt(rnd());
		// min, max�Ԃ̈�l����
		std::uniform_int_distribution<int> randRange(min, max);

		return randRange(mt);
	}

	/**
	* @fn
	* �����̐���(float�^)
	* @brief ����min,max�̊Ԃ̗����𐶐�����
	* @param (min) �ŏ��l
	* @param (max) �ő�l
	* @return min,max�̊Ԃ̗���
	*/
	static float randRange(float min, float max)
	{
		///FIXME �t�B�[���h��
		// �񌈒�I�ȗ���������ŃV�[�h������𐶐�
		std::random_device rnd;
		// �����Z���k�E�c�C�X�^ �����͏����V�[�h�l �t�@���N�^��n��
		std::mt19937 mt(rnd());
		// min, max�Ԃ̈�l����
		std::uniform_real_distribution<float> randRange(min, max);

		return randRange(mt);
	}

	/**
	* @fn
	* �I�C���[�p(Vector3)����]�s��(Matrix4x4)���璊�o����
	* @param (euler) �I�C���[�p(�o��)
	* @param (rot) ��]�s��
	*/
	static Vector3 computeEulerAngleFromMatrix(const Vector3& euler, const Matrix4x4 &rot)
	{
		Vector3 out;
		float threshold = 0.001f;

		if (abs(rot.m[2][1] - 1.0f) < threshold) 
		{
			// rot(2,1) = sin(x) = 1�̎�
			out.x = (float)D3DXToDegree(D3DX_PI / 2.0f);
			out.y = 0;
			out.z = (float)D3DXToDegree(atan2(rot.m[1][0], rot.m[0][0]));
		}
		else if (abs(rot.m[2][1] + 1.0f) < threshold) 
		{
			// rot(2,1) = sin(x) = -1�̎�
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