/**
* @file PlayerSettingDesc
* @brief プレイヤー生成時の設定項目をまとめた記述子
* @author Ryunosuke Honda.
*/
#pragma once

#include "MathDef.h"
#include "EPlayerIndex.h"

#include <functional>

class Bullet;

/**
*	プレイヤー生成時の設定項目をまとめた記述子
*/
struct PlayerSettingDesc
{
	//!プレイヤー番号
	EPlayerIndex mIndex;
	//!体力
	int mHP;
	//!当たり判定(境界球)のサイズ
	float mRadius;
	//!初期位置
	Vector3 mPosition;
	//!銃弾生成関数
	std::function<void(Bullet*)> mGenerateBulletFunc;
};

/****** End of File *****************************************************/
