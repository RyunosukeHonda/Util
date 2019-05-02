/**
* @file ResourceRenderer.h
* @brief リソース描画に使用するクラステンプレート(ヘッダのみ)
* @author Ryunosuke Honda.
*/
#pragma once

#include "Base.h"
#include "Manager.h"
#include "MeshRenderDesc.h"
#include <vector>

class Camera;
struct DirectionalLightDesc;

/**
*	リソース描画クラス用テンプレート
*	D = MeshRenderDesc(リソース描画に使用する記述子)
*	K = Key(連想配列登録に使用するID)
*	V = Value(連想配列に登録するデータ型。Manager内でポインタに変換されます)
*/
template<
	class K,
	class V,
	class D = MeshRenderDesc
>
class ResourceRenderer : protected Manager<K, V>
{
public:
	/**
	 * @fn
	 * デフォルトコンストラクタ
	 */
	ResourceRenderer() :
		mData()
	{}

	/**
	 * @fn
	 * 仮想デストラクタ
	 */
	virtual ~ResourceRenderer() {};

	void clear()
	{
		///描画データの管理自体は各クラスで行っているので
		///ここでディープクリアはせず
		///ベクターのクリアのみを行う
		mData.clear();
		mTransparentData.clear();
	}

	/**
	* @fn
	* 初期化
	* @brief 同形式を扱うために必要なパラメーターを初期化
	* @param (pDevice) DirectX描画機器
	* @return 正常に終了したか
	* @detail 同アプリケーション内では一度のみ呼び出されれば十分
	*/
	virtual HRESULT init(ID3D11Device* pDevice) = 0;

	/**
	* @fn
	* 記述子データの登録
	* @brief 各記述子を受け取り、アルファ値によって登録先を分岐する
	* @param (D) 記述子ポインタ
	*/
	void registerDesc(const D* pDesc)
	{
		//簡易のため記述子のディフューズ色のアルファ値で判別
		if (pDesc->mDiffuse.a > 0.999f)
		{
			mData.push_back(pDesc);
		}
		else
		{
			mTransparentData.push_back(pDesc);
		}
	}

	/**
	* @fn
	* メッシュ描画(不透過)
	* @param (pDeviceContext) DirectX描画機器
	* @param (camera) 抽象カメラクラス
	* @param (light) 平行光源
	*/
	virtual void render(ID3D11DeviceContext* pDeviceContext, const Camera* pCamera, const DirectionalLightDesc& light) = 0;

	/**
	* @fn
	* 透過メッシュ描画
	* @param (pDeviceContext) DirectX描画機器
	* @param (camera) 抽象カメラクラス
	* @param (light) 平行光源
	*/
	virtual void renderTransparent(ID3D11DeviceContext* pDeviceContext, const Camera* pCamera, const DirectionalLightDesc& light) = 0;

protected:
	//!記述子コンテナ命名
	using RenderData = std::vector<const D*>;
	//!不透過オブジェクトデータ格納コンテナ
	RenderData mData;
	//!透過オブジェクトデータコンテナ
	RenderData mTransparentData;
};

/* End of File *****************************************************/