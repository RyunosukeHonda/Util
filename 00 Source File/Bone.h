/**
* @file Bone.h
* @brief ボーン構造体
* @author Ryunosuke Honda.
*/
#pragma once

#include "Base.h"

/**
*	ボーン構造体
*/
struct Bone
{
	//!初期ポーズ（ずっと変わらない）
	Matrix4x4 mBindPose;
	//!現在のポーズ（その都度変わる）
	Matrix4x4 mNewPose;
	
	/**
	* @fn
	* コンストラクタ
	*/
	Bone()
	{
		ZeroMemory(this, sizeof(Bone));
	}
};

/****** End of File *****************************************************/
