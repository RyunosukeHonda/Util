/**
* @file FBXSkinMeshRenderDesc.h
* @brief FBXスキンメッシュ描画記述子
* @author Ryunosuke Honda.
*/
#pragma once

#include "MeshRenderDesc.h"
#include "FBXSkinMeshID.h"

/**
*	FBXスキンメッシュ描画記述子
*/
struct FBXSkinMeshRenderDesc : public MeshRenderDesc
{
	/**
	*	@fn
	*	コンストラクタ
	*/
	FBXSkinMeshRenderDesc(const FBXSkinID& id) :
		MeshRenderDesc(),
		mID(id),
		mFrame(0) {}

	//!モデルID
	FBXSkinID mID;
	//!アニメーションフレーム
	int mFrame;
};

/****** End of File *****************************************************/
