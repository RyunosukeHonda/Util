/**
* @file PlaneCollider.h
* @brief ���ʃR���C�_�[�N���X��`�t�@�C��
* @author Ryunosuke Honda.
*/
#pragma once

#include "ACollider.h"

/**
*	���ʃR���C�_�[�N���X�E����ǂɎg�p
*/
class PlaneCollider : public ACollider
{
public:
	/**
	 * @fn
	 * �R���X�g���N�^
	 */
	PlaneCollider(const Vector3& pos, const Vector3& norm);

	/**
	 * @fn
	 * �f�X�g���N�^
	 */
	virtual ~PlaneCollider();

private:
	using base = ACollider;
};

/* End of File *****************************************************/