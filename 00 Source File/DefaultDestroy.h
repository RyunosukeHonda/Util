/**
* @file DefaultDestroy.h
* @brief �폜�|���V�[�N���X
* @author Ryunosuke Honda.
*/
#pragma once



/**
*	�폜�|���V�[�N���X
*/
class DefaultDestroy
{
public:
	// �폜����
	template <class Entity>
	static void destroy(Entity instance)
	{
		delete *instance;
	}
};

/* End of File *****************************************************/