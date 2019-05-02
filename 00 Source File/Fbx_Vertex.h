/**
* @file Fbx_Vertex.h
* @brief FBX用頂点構造体
* @author Ryunosuke Honda.
*/
#pragma once

#include "MathDef.h"

/**
*	FBX用頂点構造体
*/
struct Fbx_Vertex
{
	//!座標
	Vector3 vPos;
	//!垂直方向ベクトル
	Vector3 vNorm;
	//!テクスチャUV座標
	Vector2 vTex;
};

/****** End of File *****************************************************/
