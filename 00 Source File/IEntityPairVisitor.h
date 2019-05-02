/**
* @file IEntityPairVisitor.h
* @brief �y�A�K��҃C���^�[�t�F�[�X
* @author Ryunosuke Honda.
*/
#pragma once



/**
*	�y�A�K��҃C���^�[�t�F�[�X
*/
template <class Entity>
class IEntityPairVisitor
{
public:
	// �f�X�g���N�^
	virtual ~IEntityPairVisitor() {}
	// �K�₷��
	virtual void visit(Entity, Entity) = 0;
};

/* End of File *****************************************************/