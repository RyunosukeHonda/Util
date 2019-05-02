/**
* @file ColorConstantBuffer.h
* @brief シェーダーに送るカラー情報構造体
* @author Ryunosuke Honda.
*/
#pragma once

#include "MathDef.h"

/**
*	カラー情報構造体
*/
struct ColorConstantBuffer
{
	//!アンビエント光
	Color4 ambient;
	//!ディフューズ色
	Color4 diffuse;
	//!鏡面反射
	Color4 specular;
	//!テクスチャーが貼られているメッシュかどうかのフラグ
	Vector4 texture;
};

/****** End of File *****************************************************/
