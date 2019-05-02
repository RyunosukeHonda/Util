/**
* @file SpriteConstantBuffer
* @brief スプライト描画シェーダーに情報を送るコンスタントバッファー
* @author Ryunosuke Honda.
*/
#pragma once

#include "MathDef.h"

/**
*	スプライト描画シェーダーに情報を送るコンスタントバッファー
*/
struct SpriteConstantBuffer
{
	//!ワールド行列
	Matrix4x4 mW;
	//!ワールドから射影までの変換行列
	Matrix4x4 mWVP;
	//!ライト方向
	Vector4 vLightDir;
	//!拡散反射(色)
	Color4 mColor;
	//!カメラ位置
	Vector4 vEye;
};

/****** End of File *****************************************************/
