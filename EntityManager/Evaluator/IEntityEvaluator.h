/**
* @file IEntityEvaluator.h
* @brief 評価者インターフェース
* @author Ryunosuke Honda.
*/
#pragma once



/**
*	評価者インターフェース
*/ 
template <class Entity>
class IEntityEvaluator
{
public:
	// デストラクタ
	virtual ~IEntityEvaluator() {}
	// 評価する
	virtual bool evaluate(Entity) = 0;
};

/* End of File *****************************************************/