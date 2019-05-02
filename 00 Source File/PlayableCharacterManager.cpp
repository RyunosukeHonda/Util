/**
* @file PlayableCharacterManager.cpp
* @brief ����\�L�����N�^�[�Ǘ��N���X�����t�@�C��
* @author Ryunosuke Honda.
*/
#include "PlayableCharacterManager.h"

#include "APlayableCharacter.h"
#include "EntityVisitorMemFun.h"
#include "EntityEvaluatorMemFun.h"
#include "EntityVisitorMemFun1.h"

PlayableCharacterManager::PlayableCharacterManager() :
	mPlayableCharacterList(),
	mIsEnd(false)
{
}

PlayableCharacterManager::~PlayableCharacterManager()
{
	clear();
}

void PlayableCharacterManager::add(APlayableCharacter * pc)
{
	mPlayableCharacterList.add(pc);
}

void PlayableCharacterManager::clear()
{
	mPlayableCharacterList.clear();
}

void PlayableCharacterManager::init()
{
	mIsEnd = false;

	//�S�v�f������
	EntityVisitorMemFun<APlayableCharacter, &APlayableCharacter::init> pcInit;
	mPlayableCharacterList.accept(pcInit);
}

void PlayableCharacterManager::update(IInput & input)
{
	//�S�v�f�X�V
	EntityVisitorMemFun1<APlayableCharacter, IInput&, &APlayableCharacter::update> pcUpdate(input);
	mPlayableCharacterList.accept(pcUpdate);
}

void PlayableCharacterManager::lateUpdate(IInput & input)
{
	//�S�v�f�x���X�V
	EntityVisitorMemFun1<APlayableCharacter, IInput&, &APlayableCharacter::lateUpdate> pcLateUpdate(input);
	mPlayableCharacterList.accept(pcLateUpdate);

	//���S�����v���C���[�����v���A�P�ȏ�Ȃ�Q�[���I��
	EntityEvaluatorMemFun<APlayableCharacter, &APlayableCharacter::isDead> pcDead;
	mIsEnd = mPlayableCharacterList.find(pcDead) != 0;
}

void PlayableCharacterManager::fixedUpdate(float dt)
{
	//�S�v�f�X�V(60FPS)
	EntityVisitorMemFun1<APlayableCharacter, float, &APlayableCharacter::fixedUpdate> pcFixedUpdate(dt);
	mPlayableCharacterList.accept(pcFixedUpdate);
}

void PlayableCharacterManager::draw(IRenderer & renderer)
{
	//�S�v�f�`��
	EntityVisitorMemFun1<IObject, IRenderer&, &APlayableCharacter::draw> draw(renderer);
	mPlayableCharacterList.accept(draw);
}

void PlayableCharacterManager::renderExecute(IRenderer & renderer)
{
	//�S�v���C���[�����J�����̖ڐ��ŕ`������s
	EntityVisitorMemFun1<APlayableCharacter, IRenderer&, &APlayableCharacter::renderExecute> render(renderer);
	mPlayableCharacterList.accept(render);
}

void PlayableCharacterManager::gameSet()
{
	EntityVisitorMemFun<APlayableCharacter, &APlayableCharacter::gameSet> pcGameSet;
	mPlayableCharacterList.accept(pcGameSet);
}

/* End of File *****************************************************/