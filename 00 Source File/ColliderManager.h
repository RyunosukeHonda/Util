/**
* @file ColliderManager.h
* @brief �R���C�_�[�Ǘ��N���X��`�t�@�C��
* @author Ryunosuke Honda.
*/
#pragma once

#include "EntityGroupManager.h"
#include "IAddable.h"

class ACollider;

/**
*	�R���C�_�[�Ǘ��N���X
*/
class ColliderManager : public IAddable<ACollider>
{
public:
	/**
	 * @fn
	 * �f�t�H���g�R���X�g���N�^
	 */
	ColliderManager();

	/**
	 * @fn
	 * �f�X�g���N�^
	 */
	~ColliderManager();

	/**
	* @fn
	* �R���C�_�[�ǉ�
	* @param (sphere) ���E���R���C�_�[�̃|�C���^
	*/
	void add(ACollider* collider) override;
	
	/**
	* @fn
	* �������E�c���Ă����e�ۂ��폜����
	*/
	void init();

	/**
	* @fn
	* �Փ˔���
	*/
	void collision();

private:
	//!�R���C�_�[���X�g
	EntityGroupManager<ACollider*, NoDestroy> mColliders;
};

/* End of File *****************************************************/