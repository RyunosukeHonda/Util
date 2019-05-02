/**
* @file CollisionVisitor.cpp
* @brief �R���C�_�[�Ǘ��N���X�ŏՓ˔�����s���K��҃N���X�����t�@�C��
* @author Ryunosuke Honda.
*/
#include "CollisionVisitor.h"

#include "Collision.h"
#include "SphereCollider.h"
#include "PlaneCollider.h"

void CollisionVisitor::visit(ACollider* c1, ACollider* c2)
{
	//�_�E���L���X�g���s�����Adynamic_cast�͎g�������Ȃ��̂�
	//�`��ŕ���A���S��static_cast���s��
	
	///c1�����̏ꍇ
	if (c1->Type == ERigidType::SPHERE)
	{
		///c2�����̏ꍇ
		if (c2->Type == ERigidType::SPHERE)
		{
			Collision::instance().collision(static_cast<SphereCollider*>(c1), static_cast<SphereCollider*>(c2));
			return;
		}
		///c2�����ʂ̏ꍇ
		if (c2->Type == ERigidType::PLANE)
		{
			Collision::instance().collision(static_cast<SphereCollider*>(c1), static_cast<PlaneCollider*>(c2));
			return;
		}
	}

	///c1�����ʂ̏ꍇ
	if (c1->Type == ERigidType::PLANE)
	{
		///c2�����̏ꍇ
		if (c2->Type == ERigidType::SPHERE)
		{
			Collision::instance().collision(static_cast<SphereCollider*>(c2), static_cast<PlaneCollider*>(c1));
			return;
		}
		///c2�����ʂ̏ꍇ
		if (c2->Type == ERigidType::PLANE)
		{
			Collision::instance().collision(static_cast<PlaneCollider*>(c1), static_cast<PlaneCollider*>(c2));
			return;
		}
	}
}

/* End of File *****************************************************/