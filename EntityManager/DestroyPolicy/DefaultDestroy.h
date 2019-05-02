/**
* @file DefaultDestroy.h
* @brief 削除ポリシークラス
* @author Ryunosuke Honda.
*/
#pragma once



/**
*	削除ポリシークラス
*/
class DefaultDestroy
{
public:
	// 削除する
	template <class Entity>
	static void destroy(Entity instance)
	{
		delete *instance;
	}
};

/* End of File *****************************************************/