/**
* @file MeshRenderDesc
* @brief メッシュ描画記述子テンプレート・モデルの種類ごとに継承して使用
* @author Ryunosuke Honda.
*/
#pragma once

#include "Transform.h"

/**
*	メッシュ描画記述子テンプレート・モデルの種類ごとに継承して使用
*/
struct MeshRenderDesc
{
	/**
	* @fn
	* コンストラクタ
	*/
	MeshRenderDesc() :
		mpTransform(nullptr),
		mAmbient(0, 0, 0, 0),
		mDiffuse(1, 0, 1, 1),
		mSpecular(0, 0, 0, 0) {}

	/**
	* @fn
	* 仮想デストラクタ・主に継承して使用するため
	*/
	virtual ~MeshRenderDesc() {}

	//!トランスフォーム情報
	Transform* mpTransform;
	//!アンビエント色(環境)・テクスチャの色に加算する
	Color4 mAmbient;
	//!ディフューズ色(拡散反射)・テクスチャの色に加算する
	Color4 mDiffuse;
	//!スペキュラー色(鏡面反射)・テクスチャの色に加算する
	Color4 mSpecular;
};

/****** End of File *****************************************************/
