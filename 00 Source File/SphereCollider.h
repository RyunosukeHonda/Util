/**
* @file SphereCollider.h
* @brief ���E���R���C�_�[�N���X��`�t�@�C��
* @author Ryunosuke Honda.
*/
#pragma once

#include "ACollider.h"

/**
*	���E���R���C�_�[
*/
class SphereCollider : public ACollider
{
public:
	/**
	 * @fn
	 * �R���X�g���N�^
	 */
	SphereCollider(float radius);

	/**
	 * @fn
	 * ���z�f�X�g���N�^
	 */
	virtual ~SphereCollider();

protected:
	PROPERTY_READWRITE(float, Radius);

private:
	using base = ACollider;
};

/* End of File *****************************************************/