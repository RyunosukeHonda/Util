/**
* @file UIQuadRenderDesc
* @brief UI矩形描画記述子
* @author Ryunosuke Honda.
*/
#pragma once

#include "ShaderTextureID.h"
#include "RectTransform.h"

/**
*	UI矩形描画記述子
*/
struct UIQuadRenderDesc
{
	/**
	* @fn
	* コンストラクタ
	*/
	UIQuadRenderDesc(const ShaderTextureID& id) :
		mID(id),
		mDiffuse(0, 0, 0, 1),
		mpRect(nullptr),
		mTime(0.0f)
	{}

	//!テクスチャ番号
	ShaderTextureID mID;
	//!ディフューズ色
	Color4 mDiffuse;
	//!2Dトランスフォーム
	RectTransform* mpRect;
	//!アニメーション時間
	float mTime;
};

/****** End of File *****************************************************/
