/**
* @file GameMainBattle.cpp
* @brief ゲームメインシーン状態・バトルクラス定実装ファイル
* @author Ryunosuke Honda.
*/
#include "GameMainBattle.h"

#include "PlayableCharacterManager.h"
#include "UIImageObject.h"

#include <unordered_map>
#include "EPlayerIndex.h"

GameMainBattle::GameMainBattle(PlayableCharacterManager* pcManager) :
	mpPlayableCharacterManager(pcManager),
	mObjManager()
{
	//プレイヤー番号をUIポジションに変換するマップ、とりあえず二人分
	std::unordered_map<int, Vector2> indexToPosition;
	indexToPosition[EPlayerIndex::ONE] = Vector2(0, 200);
	indexToPosition[EPlayerIndex::TWO] = Vector2(0, -200);

	//プレイヤー人数分ループ
	for (int i = 0; i < GameDef::PLAYER_COUNT; i++)
	{
		//ターゲットマーカー生成
		UIImageObject* marker = new UIImageObject(TextureID::MARKER);
		marker->Position = { indexToPosition[i] };
		marker->Scale = { 100, 100 };
		marker->SortingLayer = 0;
		mObjManager.add(marker);
	}
}

GameMainBattle::~GameMainBattle()
{
}

void GameMainBattle::init()
{

}

void GameMainBattle::shutdown()
{
}

bool GameMainBattle::isEnd()
{
	return mpPlayableCharacterManager->IsEnd;
}

EGameMainState GameMainBattle::next()
{
	return EGameMainState::GAMESET;
}

void GameMainBattle::update(IInput & input)
{
	mpPlayableCharacterManager->update(input);
}

void GameMainBattle::fixedUpdate(float dt)
{
}

void GameMainBattle::lateUpdate(IInput & input)
{
}

void GameMainBattle::draw(IRenderer & renderer)
{
	mObjManager.draw(renderer);
}

/* End of File *****************************************************/