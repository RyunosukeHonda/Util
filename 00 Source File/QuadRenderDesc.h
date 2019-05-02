/**
* @file QuadRendererDesc
* @brief シェーダーテクスチャ描画用矩形情報記述子
* @author Ryunosuke Honda.
*/
#pragma once

#include "MeshRenderDesc.h"
#include "ShaderTextureID.h"

/**
*	シェーダーテクスチャ描画用矩形情報記述子
*/
struct QuadRenderDesc : MeshRenderDesc
{
	/**
	* @fn
	* コンストラクタ
	*/
	QuadRenderDesc(const ShaderTextureID& id) :
		MeshRenderDesc(),
		mID(id),
		mTime(0.0f)
	{}

	/**
	* @fn
	* デストラクタ
	*/
	~QuadRenderDesc() {}

	//!シェーダーテクスチャID
	ShaderTextureID mID;
	//!アニメーション時間
	float mTime;
};

/****** End of File *****************************************************/
