/**
* @file DirectionalLightDesc
* @brief 指向性ライト(平行光源)情報記述子
* @author Ryunosuke Honda.
*/
#pragma once

#include "MathDef.h"

/**
*	指向性ライト(平行光源)情報記述子
*/
struct DirectionalLightDesc
{
	//!ライト方向
	Vector3 direction;
	//!ライト強さ
	float intencity;
};

/****** End of File *****************************************************/
