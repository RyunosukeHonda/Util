/**
* @file NoDestroy.h
* @brief �폜���Ȃ��|���V�[�N���X
* @author Ryunosuke Honda.
*/
#pragma once



/**
*	�폜���Ȃ��|���V�[�N���X
*/
class NoDestroy
{
public:
	// �폜���Ȃ�
	template <class Entity>
	static void destroy(Entity instance) {}
};

/* End of File *****************************************************/