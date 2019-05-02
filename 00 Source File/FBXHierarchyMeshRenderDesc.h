/**
* @file FBXHierarchyMeshRenderDesc
* @brief FBX階層メッシュ描画記述子
* @author Ryunosuke Honda.
*/
#pragma once

#include "MeshRenderDesc.h"
#include "FBXHierarchyMeshID.h"

/**
*	FBX階層メッシュ描画記述子
*/
struct FBXHierarchyMeshRenderDesc : public MeshRenderDesc
{
	/**
	*	@fn
	*	コンストラクタ
	*/
	FBXHierarchyMeshRenderDesc(const FBXHierarchyID& id) :
		MeshRenderDesc(),
		mID(id),
		mFrame(0)
	{
	}

	//!モデルID
	FBXHierarchyID mID;
	//!アニメーションフレーム
	int mFrame;
};

/****** End of File *****************************************************/
