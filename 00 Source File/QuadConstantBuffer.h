/**
* @file QuadConstantBuffer
* @brief 矩形描画シェーダーに情報を送るコンスタントバッファー
* @author Ryunosuke Honda.
*/
#pragma once

#include "MathDef.h"

/**
*	矩形描画シェーダーに情報を送るコンスタントバッファー
*/
struct QuadConstantBuffer
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
	//!シェーダー内のアニメーション時間
	Vector4 mTime;
};

/****** End of File *****************************************************/
