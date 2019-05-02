/**
* @file Gun.h
* @brief 銃クラス定義ファイル
* @author Ryunosuke Honda.
*/
#pragma once

#include "IShotable.h"
#include "Timer.h"

#include <functional>

class ACharacter;
class ACollider;
class Bullet;

/**
*	銃クラス
*	プレイヤーに持たせて射撃を行う
*/
class Gun : public IShotable
{
public:
	/**
	 * @fn
	 * コンストラクタ・上位の銃弾生成関数を保持
	 */
	Gun(const std::function<void(Bullet*)> generateBulletFunc);

	/**
	 * @fn
	 * デストラクタ
	 */
	~Gun();

	// IShotable を介して継承されました
	virtual void shot(const Transform* parent) override;
	virtual void update() override;

protected:
	//!連射速度・~秒に一発発射
	Timer mFireRate;
	//!銃弾生成用の関数を設定
	std::function<void(Bullet*)> mGenerateBulletFunc;
};

/* End of File *****************************************************/