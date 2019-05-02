/**
* @file ShaderLightEyevec.h
* @brief シェーダー用のコンスタントバッファーのアプリ側構造体
* @author Ryunosuke Honda.
*/
#pragma once

#include "Base.h"

/**
*	シェーダー用のコンスタントバッファーのアプリ側構造体 もちろんシェーダー内のコンスタントバッファーと一致している必要あり
*/
struct ShaderLightEyevec
{
	//!ライト方向
	Vector4 vLightDir;
	//!カメラ位置
	Vector4 vEye;
};

/****** End of File *****************************************************/
