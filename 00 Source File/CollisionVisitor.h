/**
* @file CollisionVisitor.h
* @brief �R���C�_�[�Ǘ��N���X�ŏՓ˔�����s���K��҃N���X��`�t�@�C��
* @author Ryunosuke Honda.
*/
#pragma once

#include "IEntityPairVisitor.h"

class ACollider;

/**
*	�R���C�_�[�Ǘ��N���X�ŏՓ˔�����s���K��҃N���X
*/
class CollisionVisitor : public IEntityPairVisitor<ACollider*>
{
public:
	// IEntityPairVisitor ����Čp������܂���
	virtual void visit(ACollider* s1, ACollider* s2) override;
};

/* End of File *****************************************************/