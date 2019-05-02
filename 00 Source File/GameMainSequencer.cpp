/**
* @file GameMainSequencer.cpp
* @brief ゲームメインシーンシーケンサークラス実装ファイル
* @author Ryunosuke Honda.
*/
#include "GameMainSequencer.h"

GameMainSequencer::GameMainSequencer()
{
}

GameMainSequencer::~GameMainSequencer()
{
}

void GameMainSequencer::update(IInput & input)
{
	mCurrentState->update(input);
}

void GameMainSequencer::fixedUpdate(float dt)
{
	mCurrentState->fixedUpdate(dt);
}

void GameMainSequencer::lateUpdate(IInput & input)
{
	mCurrentState->lateUpdate(input);
	stateEndCheck();
}

void GameMainSequencer::draw(IRenderer & renderer)
{
	mCurrentState->draw(renderer);
}

/* End of File *****************************************************/