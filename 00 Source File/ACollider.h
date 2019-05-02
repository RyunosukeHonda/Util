/**
* @file ACollider.h
* @brief 抽象当たり判定定義クラス
* @author Ryunosuke Honda.
*/
#pragma once

#include "ARigidBody.h"
#include <unordered_map>

class SphereCollider;
class PlaneCollider;

/**
*	抽象当たり判定クラス
*/
class ACollider : public ARigidBody
{
public:
	/**
	 * @fn
	 * コンストラクタ
	 */
	ACollider(const ERigidType& type);

	/**
	 * @fn
	 * 仮想デストラクタ
	 */
	virtual ~ACollider();

	/**
	* @fn
	* 衝突時に呼び出される処理
	* @brief Enter,Stay,Exitの分岐を行う
	* @param (other) 衝突判定を行った相手のポインタ
	* @param (isCol) 衝突していたか
	*/
	void result(ACollider* other, bool isCol);

	/**
	* @fn
	* 不正レイヤーの検知
	* @return 不正ならtrue
	*/
	bool isInvalid() const;

protected:
	/**
	* @fn
	* 衝突時、最初の１フレームのみ呼び出される処理
	* @param (other) 衝突判定を行った相手のポインタ
	*/
	virtual void onCollisionEnter(ACollider* other) {}

	/**
	* @fn
	* 衝突している間呼び出される処理
	* @param (other) 衝突判定を行った相手のポインタ
	*/
	virtual void onCollisionStay(ACollider* other) {}

	/**
	* @fn
	* 衝突が終わった瞬間、１フレームのみ呼び出される処理
	* @param (other) 衝突判定を行った相手のポインタ
	*/
	virtual void onCollisionExit(ACollider* other) {}

	//!トリガーとして使用するかどうか・衝突時物理挙動を行うかどうか判断する
	PROPERTY_READWRITE(bool, IsTrigger);

private:
	using base = ARigidBody;
	using ColliderInfo = unordered_map<ACollider*, bool>;

	//!他のコライダーとの衝突情報保管マップ
	ColliderInfo mInfo;
};

/* End of File *****************************************************/