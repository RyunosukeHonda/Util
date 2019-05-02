/**
* @file SphereCollider.h
* @brief 境界球コライダークラス定義ファイル
* @author Ryunosuke Honda.
*/
#pragma once

#include "ACollider.h"

/**
*	境界球コライダー
*/
class SphereCollider : public ACollider
{
public:
	/**
	 * @fn
	 * コンストラクタ
	 */
	SphereCollider(float radius);

	/**
	 * @fn
	 * 仮想デストラクタ
	 */
	virtual ~SphereCollider();

protected:
	PROPERTY_READWRITE(float, Radius);

private:
	using base = ACollider;
};

/* End of File *****************************************************/