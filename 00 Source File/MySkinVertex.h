/**
* @file MySkinVertex.h
* @brief スキンメッシュ用頂点構造体
* @author Ryunosuke Honda.
*/
#pragma once

#include "Base.h"

/**
*	スキンメッシュ用 頂点構造体
*/
struct MySkinVertex
{
	/**
	* @fn
	* コンストラクタ
	*/
	MySkinVertex()
	{
		ZeroMemory(this, sizeof(MySkinVertex));
	}

	//!頂点位置
	Vector3 vPos;
	//!頂点法線
	Vector3 vNorm;
	//!UV座標
	Vector2 vTex;
	//!ボーン　番号
	UINT bBoneIndex[4];
	//!ボーン　重み
	float bBoneWeight[4];
};

/****** End of File *****************************************************/
