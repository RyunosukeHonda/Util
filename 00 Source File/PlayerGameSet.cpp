/**
* @file PlayerGameSet.cpp
* @brief プレイヤー決着状態クラス実装ファイル
* @author Ryunosuke Honda.
*/
#include "PlayerGameSet.h"

#include "Player.h"
#include "Screen.h"

PlayerGameSet::PlayerGameSet(Player* pPlayer) :
	mpPlayer(pPlayer),
	mResultImage(TextureID::WIN, 1.0f)
{
	//プレイヤー番号に応じたUI位置を設定
	mResultImage.Position = { 0, (float)Screen::WINDOW_HEIGHT / 4.0f - (float)Screen::WINDOW_HEIGHT / 2.0f * (float)pPlayer->Index };
}

PlayerGameSet::~PlayerGameSet()
{
}

void PlayerGameSet::init()
{
	//死んでいるかどうかで勝敗画像を選択
	if (mpPlayer->isDead())
	{
		mResultImage.Scale = { 500, 100 };
		mResultImage.setID(TextureID::LOSE);
	}
	else
	{
		mResultImage.Scale = { 500, 100 };
		mResultImage.setID(TextureID::WIN);
	}
	mResultImage.init();
}

void PlayerGameSet::shutdown()
{
}

bool PlayerGameSet::isEnd()
{
	//自動的にシーンが終了するので遷移する必要なし
	return false;
}

EPlayerState PlayerGameSet::next()
{
	//実際に遷移はしない
	return EPlayerState::IDLE;
}

void PlayerGameSet::update(IInput & input)
{

}

void PlayerGameSet::fixedUpdate(float dt)
{
	//死んでいたら倒れさせる
	if (mpPlayer->isDead())
	{
		mpPlayer->EulerAngle += {0, 0, 0.5f};
	}
}

void PlayerGameSet::lateUpdate(IInput & input)
{
}

void PlayerGameSet::draw(IRenderer & renderer)
{
	mResultImage.draw(renderer);
}

void PlayerGameSet::onCollisionEnter(ACollider * other)
{
}

void PlayerGameSet::gameSet()
{
}

/* End of File *****************************************************/