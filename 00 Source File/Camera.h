/**
* @file Camera.h
* @brief カメラクラス定義ファイル
* ビュー・プロジェクション行列、ビューポート、レイヤーのカリング情報を持つ
* 主に継承して使用します
* @author Ryunosuke Honda.
*/
#pragma once

#include "Transform.h"

/**
*	カメラクラス(最低限)
*/
class Camera : public Transform
{
public:
	/**
	 * @fn
	 * デフォルトコンストラクタ
	 */
	Camera();

	/**
	 * @fn
	 * デストラクタ
	 */
	virtual ~Camera() {}

	/**
	* @fn
	* 更新処理
	* @brief パラメータから各行列の設定を行う
	*/
	virtual void update();

	/**
	* @fn
	* カリングレイヤー設定
	* @brief レイヤーを設定することでこのカメラの画面描画を行うときにカリングする
	* @param (layer) カリングしたいレイヤー(可変長)
	* @detail ELayer以外の値を設定するとコンパイル時にエラーになります
	*/
	template<typename... VA_Layer>
	inline void setCullingLayer(const VA_Layer&... layer)
	{
		mCullingLayer += calcLayerMask(layer...);
	}

	/**
	* @fn
	* カリングするかどうか
	* @param (layer) チェックするレイヤー
	* @return カリングするレイヤーならtrue
	*/
	bool isCulling(const ELayer& layer) const;

private:
	/**
	* @fn
	* レイヤーマスク計算
	* @param (layer) 加算するレイヤー
	* @detail レイヤー設定時にのみ呼び出されます
	*/
	unsigned int calcLayerMask(const ELayer & layer);
	

private:
	///基底クラス命名
	using base = Transform;

protected:
	/**
	* @fn
	* ビュー、プロジェクション行列の設定(更新)
	*/
	void calcViewProj();

	///以下プロパティ

	//!注視位置
	PROPERTY_READWRITE(Vector3, LookPt);
	//!上方向ベクトル
	PROPERTY_READWRITE(Vector3, UpVec);
	//!ビュー行列
	PROPERTY_READONLY(Matrix4x4, View);
	//!プロジェクション行列
	PROPERTY_READONLY(Matrix4x4, Proj);
	//!このカメラを使用して描画をするときに使用するビューポート
	PROPERTY_READWRITE(D3D11_VIEWPORT, Viewport);
	//!レイヤーのカリングに使う整数値の命名
	using CullingLayer = unsigned int;
	//!このカメラを使用してレンダリングを行うときにカリングされるレイヤー
	CullingLayer mCullingLayer;
};

/* End of File *****************************************************/