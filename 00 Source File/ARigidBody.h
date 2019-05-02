/**
* @file ARigidBody.h
* @brief ���̒��ۃN���X��`�t�@�C��
* @author Ryunosuke Honda.
*/
#pragma once

#include "Transform.h"
#include "ERigidType.h"

/**
*	���̒��ۃN���X�E�R���C�_�[�Ɍp�������ĕ����������s���܂�
*/
class ARigidBody : public Transform
{
public:
	/**
	* @fn
	* �R���X�g���N�^
	* @param (type) ���̂̌`����w��
	*/
	ARigidBody(const ERigidType& type);

	/**
	 * @fn
	 * ���z�f�X�g���N�^
	 */
	virtual ~ARigidBody();

	void addForce(Vector3& force);

protected:
	/**
	* @fn
	* FPS�����X�V�E���������̌v�Z���s��
	* @param (dt) �t���[���΍�����
	*/
	void fixedUpdate(float dt);

private:
	/**
	* @fn
	* ������
	*/
	void init();

protected:
	//!�d�́E�萔
	static const float GRAVITY;
	//!�`��E�v���p�e�B��Getter�̂݌��J
	PROPERTY_READONLY(ERigidType, Type);
	//!�d�͂����Z���邩�ǂ���
	PROPERTY_READWRITE(bool, UseGravity);
	//!��]���Œ肷�邩�ǂ���
	PROPERTY_READWRITE(bool, FreezeRotation);
	//!�O��(N)
	PROPERTY_READWRITE(Vector3, Force);
	//!�����x(m/ss)
	Vector3 Acc;
	//!���x(m/s)     
	Vector3 Vel;
	//�g���N(N�Em)
	PROPERTY_READWRITE(Vector3, Torque);
	//�p�����xa(rad/ss)
	PROPERTY_READWRITE(Vector3, Alpha);
	//�p���x��(rad/s)
	PROPERTY_READWRITE(Vector3, Omega);
	//!����(kg)
	PROPERTY_READWRITE(float, Mass);
	//!�����C�W��
	PROPERTY_READWRITE(float, UK);
	//!�Î~���C�W��
	PROPERTY_READWRITE(float, US);
	//!�����W��
	PROPERTY_READWRITE(float, E);
	//!�Փ˓_
	PROPERTY_READWRITE(Vector3, Pt);

private:
	//!���N���X����
	using base = Transform;
	//�p�^����
	Vector3 mAngMomentum;
	//�I�u�W�F�N�g���W�n�̃�
	Vector3 mOmegaObj;
	//�I�u�W�F�N�g���W�̃g���N
	Vector3 mTorqueObj;
	//��]�p��
	Quaternion mPosture;
	//�������[�����g
	Matrix4x4 mInertia;
	//�������[�����g�̋t�s��
	Matrix4x4 mInverseInertia;
};

/* End of File *****************************************************/