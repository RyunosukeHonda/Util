/**
* @file MyVertex.h
* @brief 頂点構造体
* @author Ryunosuke Honda.
*/
#pragma once

#include "MathDef.h"

/**
*	頂点構造体
*/
struct MyVertex
{
	//!頂点位置
	Vector3 vPos;
	//!垂線ベクトル
	Vector3 vNorm;
	//!UV座標
	Vector2 vTex;
};

/****** End of File *****************************************************/
