/**
* @file PlaneCollider.cpp
* @brief ���ʃR���C�_�[�N���X�����t�@�C��
* @author Ryunosuke Honda.
*/
#include "PlaneCollider.h"

#include "Collision.h"

PlaneCollider::PlaneCollider(const Vector3& pos, const Vector3& norm):
	base(ERigidType::PLANE)
{
	LocalPosition = pos;
	//������x�N�g����@���x�N�g���Ƃ��Ďg�p����
	mUp = norm;
}

PlaneCollider::~PlaneCollider()
{
}

/* End of File *****************************************************/