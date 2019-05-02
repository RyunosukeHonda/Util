/**
* @file UIImageRenderDesc
* @brief UI画像描画記述子
* @author Ryunosuke Honda.
*/
#pragma once

#include "TextureID.h"
#include "RectTransform.h"

/**
*	UI画像描画記述子
*/
struct UIImageRenderDesc
{
	/**
	* @fn
	* コンストラクタ
	*/
	UIImageRenderDesc(const TextureID& id) :
		mID(id),
		mDiffuse(0, 0, 0, 1),
		mpRect(nullptr)
	{}

	//!テクスチャ番号
	TextureID mID;
	//!ディフューズ色
	Color4 mDiffuse;
	//!2Dトランスフォーム
	RectTransform* mpRect;
};

/****** End of File *****************************************************/
