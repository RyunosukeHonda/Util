/**
* @file IEntityVisitor.h
* @brief �K��҃C���^�[�t�F�[�X
* @author Ryunosuke Honda.
*/
#pragma once



/**
*	�K��҃C���^�[�t�F�[�X
*/
template <class Entity>
class IEntityVisitor
{
public:
	// �f�X�g���N�^
	virtual ~IEntityVisitor() {}
	// �K�₷��
	virtual void visit(Entity) = 0;
};

/* End of File *****************************************************/