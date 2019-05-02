/**
* @file Gun.cpp
* @brief 銃クラス実装ファイル
* @author Ryunosuke Honda.
*/
#include "Gun.h"
#include "Bullet.h"
#include "Transform.h"

#include "SoundManager.h"

Gun::Gun(const std::function<void(Bullet*)> generateBulletFunc) :
	mFireRate(1.0f),
	mGenerateBulletFunc(generateBulletFunc)
{
}

Gun::~Gun()
{
}

void Gun::shot(const Transform* parent)
{
	//連射タイマーが終了していれば撃てる
	if (mFireRate.isEnd())
	{
		int index_to_layer = 2;
		float shiftAmount = 2.0f;
		Bullet* b = new Bullet(parent->Position + parent->Forward * shiftAmount, parent->Forward);
		b->Layer = static_cast<ELayer>(parent->Layer + index_to_layer);
		mGenerateBulletFunc(b);
		mFireRate.init();
		SoundManager::instance().play(SoundID::FIRE, false);
	}
}

void Gun::update()
{
	mFireRate.update();
}

/* End of File *****************************************************/