/**
* @file GameMainGameSet.cpp
* @brief �Q�[�����C���V�[����ԁE�����N���X�����t�@�C��
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
	//��Ԃ͏I���Ȃ����A�^�C�}�[�I�����ɃV�[�����I������
	return false;
}

EGameMainState GameMainGameSet::next()
{
	//���ۂɑJ�ڂ͂��Ȃ�
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