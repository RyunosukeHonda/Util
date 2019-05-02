/**
* @file NoDestroy.h
* @brief 削除しないポリシークラス
* @author Ryunosuke Honda.
*/
#pragma once



/**
*	削除しないポリシークラス
*/
class NoDestroy
{
public:
	// 削除しない
	template <class Entity>
	static void destroy(Entity instance) {}
};

/* End of File *****************************************************/