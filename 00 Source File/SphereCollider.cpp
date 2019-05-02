/**
* @file SphereCollider.cpp
* @brief ���E���R���C�_�[�N���X�����t�@�C��
* @author Ryunosuke Honda.
*/
#include "SphereCollider.h"

#include "Collision.h"

SphereCollider::SphereCollider(float radius) :
	base(ERigidType::SPHERE),
	mRadius(radius)
{
}

SphereCollider::~SphereCollider()
{
}

/* End of File *****************************************************/