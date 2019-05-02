/**
* @file SpriteRenderDesc
* @brief スプライト描画記述子
* @author Ryunosuke Honda.
*/
#pragma once

#include "MeshRenderDesc.h"
#include "TextureID.h"

/**
*	スプライト描画記述子
*/
struct SpriteRenderDesc : public MeshRenderDesc
{
	/**
	* @fn
	* コンストラクタ
	*/
	SpriteRenderDesc(const TextureID& id) :
		MeshRenderDesc(),
		mID(id)
	{}

	//!テクスチャID
	TextureID mID;
};

/****** End of File *****************************************************/
