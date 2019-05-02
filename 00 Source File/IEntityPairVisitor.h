/**
* @file IEntityPairVisitor.h
* @brief ペア訪問者インターフェース
* @author Ryunosuke Honda.
*/
#pragma once



/**
*	ペア訪問者インターフェース
*/
template <class Entity>
class IEntityPairVisitor
{
public:
	// デストラクタ
	virtual ~IEntityPairVisitor() {}
	// 訪問する
	virtual void visit(Entity, Entity) = 0;
};

/* End of File *****************************************************/