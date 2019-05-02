/**
* @file Transform.h
* @brief 3�����g�����X�t�H�[�����N���X��`�t�@�C��
* @author Ryunosuke Honda.
*/
#pragma once

#include "Base.h"
#include "ETag.h"
#include "ELayer.h"
#include "EntityManager.h"

/**
*	3�����g�����X�t�H�[�����N���X
*	�I�u�W�F�N�g�̈ʒu�A��]�A�X�P�[���̑�
*	�^�O�⃌�C���[�A�����Ȃǂ������N���X
*/
class Transform : public CElement
{
public:
	/**
	 * @fn
	 * �R���X�g���N�^
	 */
	Transform();

	/**
	 * @fn
	 * �f�X�g���N�^
	 */
	virtual ~Transform();

	/**
	* @fn
	* �g�����X�t�H�[���������[���h���W�n�ɕϊ����Ĉ����Ɋi�[����
	* @param (world) ���[���h���W���i�[����Matrix�|�C���^
	*/
	void makeWorld(Matrix4x4* world);

	/**
	* @fn
	* �e�I�u�W�F�N�g�̐ݒ�
	* @param (parent) �e�I�u�W�F�N�g�̃g�����X�t�H�[��
	* @detail �����ɐe�I�u�W�F�N�g�̎q�z��ɓo�^����
	*/
	void setParent(Transform* parent);

	/**
	* @fn
	* �e�I�u�W�F�N�g�擾
	* @return �e�g�����X�t�H�[���̃|�C���^
	*/
	Transform* getParent();

	/**
	* @fn
	* �q�I�u�W�F�N�g�擾
	* @param (index) �q�z���̃C���f�b�N�X
	* @return �q�g�����X�t�H�[���̃|�C���^
	*/
	//Transform* getChild(int index);

	/**
	* @fn
	* �g�����X�t�H�[���̃��[�g���擾
	* @return ���[�g(��ԏ�̊K�w)
	*/
	Transform* getRoot();

	/**
	* @fn
	* ���g���g�����X�t�H�[���̃��[�g���ǂ������擾
	* @return ���[�g�Ȃ�true
	*/
	bool isRoot();

	void lookAt(const Vector3& target);

private:
	///�ȉ��A�l�ݒ莞�ɑΉ������l�𓯎��ɍX�V����֐�

	void setChild(Transform* child);

	void calcLocalPosition(const Vector3& localPosition);

	void calcPosition(const Vector3& position);

	void calcLocalEulerAngle(const Vector3& euler);

	void calcEulerAngle(const Vector3& euler);

	void calcLocalScale(const Vector3& scale);

	void calcScale(const Vector3& localScale);

	void calcRotation();

	void calcDirection();

	void updateChildren();

	///�ȉ��v���p�e�B

	//!���[�J���ʒu
	PROPERTY_READWRITE_ADDSETTER(Vector3, LocalPosition, calcPosition);
	//!���[�J���̌���(�I�C���[�p�ADegree�Œ�`)
	PROPERTY_READWRITE_ADDSETTER(Vector3, LocalEulerAngle, calcEulerAngle);
	//!���[�J���X�P�[��(�i1,1,1�j�ŏ�����)
	PROPERTY_READWRITE_ADDSETTER(Vector3, LocalScale, calcScale);
	//!���[���h�ʒu
	PROPERTY_READWRITE_ADDSETTER(Vector3, Position, calcLocalPosition);
	//!���[���h����(�I�C���[�p�ADegree�Œ�`)
	PROPERTY_READWRITE_ADDSETTER(Vector3, EulerAngle, calcLocalEulerAngle);
	//!���[���h�X�P�[��
	PROPERTY_READWRITE_ADDSETTER(Vector3, Scale, calcLocalScale);
	//!���[���h���[�e�[�V����(�s��ŕێ�)
	PROPERTY_READONLY(Matrix4x4, Rotation);
	//!�O�����x�N�g��
	PROPERTY_READONLY(Vector3, Forward);
	//!������x�N�g��
	PROPERTY_READONLY(Vector3, Up);
	//!�E�����x�N�g��
	PROPERTY_READONLY(Vector3, Right);
	//!�I�u�W�F�N�g�^�O
	PROPERTY_READWRITE(ETag, Tag);
	//!�I�u�W�F�N�g���C���[
	PROPERTY_READWRITE(ELayer, Layer);

private:
	//!�e�I�u�W�F�N�g�̃g�����X�t�H�[��
	Transform* mParent;
	//!�q�I�u�W�F�N�g�z��
	EntityManager<Transform*, NoDestroy> mChildren;
};

/* End of File *****************************************************/