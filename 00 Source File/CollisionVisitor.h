/**
* @file CollisionVisitor.h
* @brief コライダー管理クラスで衝突判定を行う訪問者クラス定義ファイル
* @author Ryunosuke Honda.
*/
#pragma once

#include "IEntityPairVisitor.h"

class ACollider;

/**
*	コライダー管理クラスで衝突判定を行う訪問者クラス
*/
class CollisionVisitor : public IEntityPairVisitor<ACollider*>
{
public:
	// IEntityPairVisitor を介して継承されました
	virtual void visit(ACollider* s1, ACollider* s2) override;
};

/* End of File *****************************************************/