/**
* @file IEntityEvaluator.h
* @brief �]���҃C���^�[�t�F�[�X
* @author Ryunosuke Honda.
*/
#pragma once



/**
*	�]���҃C���^�[�t�F�[�X
*/ 
template <class Entity>
class IEntityEvaluator
{
public:
	// �f�X�g���N�^
	virtual ~IEntityEvaluator() {}
	// �]������
	virtual bool evaluate(Entity) = 0;
};

/* End of File *****************************************************/