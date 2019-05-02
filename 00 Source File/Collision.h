/**
* @file Collision.h
* @brief 当たり判定クラス定義ファイル
* @author Ryunosuke Honda.
*/
#pragma once

#include "Singleton.h"

struct ID3D11Device;
struct ID3D11DeviceContext;

class SphereCollider;
class PlaneCollider;

class SphereXSphereJudge;

/**
*	当たり判定クラス・シングルトンで使用
*	クラス肥大化を抑制するため計算自体は各機能クラスが行う
*/
class Collision : public Singleton<Collision>
{
public:
	/**
	 * @fn
	 * コンストラクタ
	 */
	Collision();

	/**
	 * @fn
	 * デストラクタ
	 */
	~Collision();

	/**
	* @fn
	* 機能初期化・デバイスの保持と各計算機能の初期化
	* @param (pDevice) デバイスポインタ
	* @param (pDeviceContext) デバイスコンテキストポインタ
	* @detail 一度のみ呼び出せば十分
	*/
	void init(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext);

	/**
	* @fn
	* 衝突判定
	* @brief 境界球同士を判定
	* @param (sph1) 境界球コライダー１
	* @param (sph2) 境界球コライダー２
	* @return 衝突していればtrue
	* @detail 衝突していた場合、お互いの衝突時処理が呼び出されます
	*/
	void collision(SphereCollider* sph1, SphereCollider* sph2);

	/**
	* @fn
	* 衝突判定
	* @brief SphereとPlaneを判定
	* @param (sph) 境界球コライダー
	* @param (pln) 平面コライダー
	* @return 衝突していればtrue
	* @detail 衝突していた場合、お互いの衝突時処理が呼び出されます
	*/
	void collision(SphereCollider* sph, PlaneCollider* pln);

	/**
	* @fn
	* 衝突判定
	* @brief 平面同士を判定
	* @param (pln1) 平面コライダー１
	* @param (pln2) 平面コライダー２
	* @return 衝突していればtrue
	* @detail 衝突していた場合、お互いの衝突時処理が呼び出されます
	*/
	void collision(PlaneCollider* pln1, PlaneCollider* pln2);

private:
	//!DirectXデバイスポインタ・バッファの作成に使用
	ID3D11Device* mpDevice;
	//!DirectXデバイスコンテキストポインタ・コンピュートシェーダーの設定などに使用
	ID3D11DeviceContext* mpDeviceContext;
	//!球同士の衝突計算クラス
	SphereXSphereJudge* mpSphXSph;
};

/* End of File *****************************************************/