/**
* @file SkinShaderBone.h
* @brief スキンメッシュのシェーダー用のコンスタントバッファーのアプリ側構造体
* @author Ryunosuke Honda.
*/
#pragma once

#include "MathDef.h"

/**
*	スキンメッシュのシェーダー用のコンスタントバッファーのアプリ側構造体
*/
struct SkinShaderBone
{
	/**
	* @fn
	* コンストラクタ
	*/
	SkinShaderBone()
	{
		//行列の初期化を行う
		for (int i = 0; i < 256; i++)
		{
			D3DXMatrixIdentity(&mBone[i]);
		}
	}

	//!ボーン行列配列
	Matrix4x4 mBone[256];
};

/****** End of File *****************************************************/
