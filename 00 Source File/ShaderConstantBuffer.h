/**
* @file ShaderConstantBuffer.h
* @brief シェーダー用のコンスタントバッファーのアプリ側構造体
* @author Ryunosuke Honda.
*/
#pragma once

#include "MathDef.h"

/**
*	シェーダー用のコンスタントバッファーのアプリ側構造体
*/
struct ShaderConstantBuffer
{
	//!ワールド行列
	Matrix4x4 mW;
	//!ワールドから射影までの変換行列
	Matrix4x4 mWVP;
	//!ライト方向
	Vector4 vLightDir;
	//!カメラ位置
	Vector4 vEye;
};

/****** End of File *****************************************************/
