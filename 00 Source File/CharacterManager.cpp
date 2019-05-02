/**
* @file CharacterManager.cpp
* @brief キャラクター管理クラス実装ファイル
* @author Ryunosuke Honda.
*/
#include "CharacterManager.h"

#include "ACharacter.h"
#include "EntityVisitorMemFun.h"
#include "EntityEvaluatorMemFun.h"
#include "EntityVisitorMemFun1.h"

CharacterManager::CharacterManager() :
	mCharacterList()
{
}

CharacterManager::~CharacterManager()
{
	clear();
}

void CharacterManager::add(ACharacter * npc)
{
	mCharacterList.add(npc);
}

void CharacterManager::clear()
{
	mCharacterList.clear();
}

void CharacterManager::init()
{
	EntityVisitorMemFun<ACharacter, &ACharacter::init> npcInit;
	mCharacterList.accept(npcInit);
}

void CharacterManager::fixedUpdate(float dt)
{
	EntityVisitorMemFun1<ACharacter, float, &ACharacter::fixedUpdate> npcUpdate(dt);
	mCharacterList.accept(npcUpdate);

	EntityEvaluatorMemFun<ACharacter, &ACharacter::isDead> npcDead;
	mCharacterList.remove(npcDead);
}

void CharacterManager::draw(IRenderer & renderer)
{
	EntityVisitorMemFun1<IObject, IRenderer&, &ACharacter::draw> draw(renderer);
	mCharacterList.accept(draw);
}

/* End of File *****************************************************/