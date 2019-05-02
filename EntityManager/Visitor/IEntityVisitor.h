/**
* @file IEntityVisitor.h
* @brief 訪問者インターフェース
* @author Ryunosuke Honda.
*/
#pragma once



/**
*	訪問者インターフェース
*/
template <class Entity>
class IEntityVisitor
{
public:
	// デストラクタ
	virtual ~IEntityVisitor() {}
	// 訪問する
	virtual void visit(Entity) = 0;
};

/* End of File *****************************************************/