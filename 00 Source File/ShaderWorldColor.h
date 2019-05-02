/**
* @file ShaderWorldColor.h
* @brief シェーダー用のコンスタントバッファーのアプリ側構造体
* @author Ryunosuke Honda.
*/
#pragma once

#include "MathDef.h"

/**
*	シェーダー用のコンスタントバッファーのアプリ側構造体
*/
struct ShaderWorldColor
{
	//!ワールド行列
	Matrix4x4 mW;
	//!ワールドから射影までの変換行列
	Matrix4x4 mWVP;
	//!アンビエント光
	Color4 ambient;
	//!ディフューズ色
	Color4 diffuse;
	//!鏡面反射
	Color4 specular;
};

/****** End of File *****************************************************/
