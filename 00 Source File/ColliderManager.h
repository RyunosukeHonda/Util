/**
* @file ColliderManager.h
* @brief コライダー管理クラス定義ファイル
* @author Ryunosuke Honda.
*/
#pragma once

#include "EntityGroupManager.h"
#include "IAddable.h"

class ACollider;

/**
*	コライダー管理クラス
*/
class ColliderManager : public IAddable<ACollider>
{
public:
	/**
	 * @fn
	 * デフォルトコンストラクタ
	 */
	ColliderManager();

	/**
	 * @fn
	 * デストラクタ
	 */
	~ColliderManager();

	/**
	* @fn
	* コライダー追加
	* @param (sphere) 境界球コライダーのポインタ
	*/
	void add(ACollider* collider) override;
	
	/**
	* @fn
	* 初期化・残っていた弾丸を削除する
	*/
	void init();

	/**
	* @fn
	* 衝突判定
	*/
	void collision();

private:
	//!コライダーリスト
	EntityGroupManager<ACollider*, NoDestroy> mColliders;
};

/* End of File *****************************************************/