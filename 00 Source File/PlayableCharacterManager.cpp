/**
* @file PlayableCharacterManager.cpp
* @brief 操作可能キャラクター管理クラス実装ファイル
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

	//全要素初期化
	EntityVisitorMemFun<APlayableCharacter, &APlayableCharacter::init> pcInit;
	mPlayableCharacterList.accept(pcInit);
}

void PlayableCharacterManager::update(IInput & input)
{
	//全要素更新
	EntityVisitorMemFun1<APlayableCharacter, IInput&, &APlayableCharacter::update> pcUpdate(input);
	mPlayableCharacterList.accept(pcUpdate);
}

void PlayableCharacterManager::lateUpdate(IInput & input)
{
	//全要素遅延更新
	EntityVisitorMemFun1<APlayableCharacter, IInput&, &APlayableCharacter::lateUpdate> pcLateUpdate(input);
	mPlayableCharacterList.accept(pcLateUpdate);

	//死亡したプレイヤー数を計測、１以上ならゲーム終了
	EntityEvaluatorMemFun<APlayableCharacter, &APlayableCharacter::isDead> pcDead;
	mIsEnd = mPlayableCharacterList.find(pcDead) != 0;
}

void PlayableCharacterManager::fixedUpdate(float dt)
{
	//全要素更新(60FPS)
	EntityVisitorMemFun1<APlayableCharacter, float, &APlayableCharacter::fixedUpdate> pcFixedUpdate(dt);
	mPlayableCharacterList.accept(pcFixedUpdate);
}

void PlayableCharacterManager::draw(IRenderer & renderer)
{
	//全要素描画
	EntityVisitorMemFun1<IObject, IRenderer&, &APlayableCharacter::draw> draw(renderer);
	mPlayableCharacterList.accept(draw);
}

void PlayableCharacterManager::renderExecute(IRenderer & renderer)
{
	//全プレイヤーが持つカメラの目線で描画を実行
	EntityVisitorMemFun1<APlayableCharacter, IRenderer&, &APlayableCharacter::renderExecute> render(renderer);
	mPlayableCharacterList.accept(render);
}

void PlayableCharacterManager::gameSet()
{
	EntityVisitorMemFun<APlayableCharacter, &APlayableCharacter::gameSet> pcGameSet;
	mPlayableCharacterList.accept(pcGameSet);
}

/* End of File *****************************************************/