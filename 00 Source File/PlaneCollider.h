/**
* @file PlaneCollider.h
* @brief 平面コライダークラス定義ファイル
* @author Ryunosuke Honda.
*/
#pragma once

#include "ACollider.h"

/**
*	平面コライダークラス・床や壁に使用
*/
class PlaneCollider : public ACollider
{
public:
	/**
	 * @fn
	 * コンストラクタ
	 */
	PlaneCollider(const Vector3& pos, const Vector3& norm);

	/**
	 * @fn
	 * デストラクタ
	 */
	virtual ~PlaneCollider();

private:
	using base = ACollider;
};

/* End of File *****************************************************/