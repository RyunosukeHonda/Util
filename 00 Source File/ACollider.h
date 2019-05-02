/**
* @file ACollider.h
* @brief ���ۓ����蔻���`�N���X
* @author Ryunosuke Honda.
*/
#pragma once

#include "ARigidBody.h"
#include <unordered_map>

class SphereCollider;
class PlaneCollider;

/**
*	���ۓ����蔻��N���X
*/
class ACollider : public ARigidBody
{
public:
	/**
	 * @fn
	 * �R���X�g���N�^
	 */
	ACollider(const ERigidType& type);

	/**
	 * @fn
	 * ���z�f�X�g���N�^
	 */
	virtual ~ACollider();

	/**
	* @fn
	* �Փˎ��ɌĂяo����鏈��
	* @brief Enter,Stay,Exit�̕�����s��
	* @param (other) �Փ˔�����s��������̃|�C���^
	* @param (isCol) �Փ˂��Ă�����
	*/
	void result(ACollider* other, bool isCol);

	/**
	* @fn
	* �s�����C���[�̌��m
	* @return �s���Ȃ�true
	*/
	bool isInvalid() const;

protected:
	/**
	* @fn
	* �Փˎ��A�ŏ��̂P�t���[���̂݌Ăяo����鏈��
	* @param (other) �Փ˔�����s��������̃|�C���^
	*/
	virtual void onCollisionEnter(ACollider* other) {}

	/**
	* @fn
	* �Փ˂��Ă���ԌĂяo����鏈��
	* @param (other) �Փ˔�����s��������̃|�C���^
	*/
	virtual void onCollisionStay(ACollider* other) {}

	/**
	* @fn
	* �Փ˂��I������u�ԁA�P�t���[���̂݌Ăяo����鏈��
	* @param (other) �Փ˔�����s��������̃|�C���^
	*/
	virtual void onCollisionExit(ACollider* other) {}

	//!�g���K�[�Ƃ��Ďg�p���邩�ǂ����E�Փˎ������������s�����ǂ������f����
	PROPERTY_READWRITE(bool, IsTrigger);

private:
	using base = ARigidBody;
	using ColliderInfo = unordered_map<ACollider*, bool>;

	//!���̃R���C�_�[�Ƃ̏Փˏ��ۊǃ}�b�v
	ColliderInfo mInfo;
};

/* End of File *****************************************************/