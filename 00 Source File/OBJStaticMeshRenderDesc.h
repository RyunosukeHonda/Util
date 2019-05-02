/**
* @file OBJStaticMeshRenderDesc.h
* @brief OBJメッシュ描画記述子
* @author Ryunosuke Honda.
*/
#pragma once

#include "MeshRenderDesc.h"
#include "OBJStaticMeshID.h"

/**
*	OBJメッシュ描画記述子
*/
struct OBJStaticMeshRenderDesc : public MeshRenderDesc
{
	/**
	*	@fn
	*	コンストラクタ
	*/
	OBJStaticMeshRenderDesc(const OBJMeshID& id) :
		MeshRenderDesc(),
		mID(id)
	{}

	//!モデルID
	OBJMeshID mID;
};

/****** End of File *****************************************************/
