/**
* @file GameMainGameSet.cpp
* @brief ゲームメインシーン状態・決着クラス実装ファイル
* @author Ryunosuke Honda.
*/
#include "GameMainGameSet.h"

#include "PlayableCharacterManager.h"

GameMainGameSet::GameMainGameSet(PlayableCharacterManager* pcManager, std::function<void()> endFunc) :
	mEndFunc(endFunc),
	mTimer(3.0f),
	mpPlayableCharacterManager(pcManager)
{
}

GameMainGameSet::~GameMainGameSet()
{
}

void GameMainGameSet::init()
{
	mTimer.init();
	mpPlayableCharacterManager->gameSet();
}

void GameMainGameSet::shutdown()
{
}

bool GameMainGameSet::isEnd()
{
	//状態は終わらないが、タイマー終了時にシーンが終了する
	return false;
}

EGameMainState GameMainGameSet::next()
{
	//実際に遷移はしない
	return EGameMainState::COUNTDOWN;
}

void GameMainGameSet::update(IInput & input)
{
	mTimer.update();

	if (mTimer.isEnd())
	{
		mEndFunc();
	}
}

void GameMainGameSet::fixedUpdate(float dt)
{
}

void GameMainGameSet::lateUpdate(IInput & input)
{
}

void GameMainGameSet::draw(IRenderer & renderer)
{
}

/* End of File *****************************************************/