/**
* @file BattleMode.cpp
* @brief バトルモードシーンクラス実装ファイル
* @author Ryunosuke Honda.
*/
#include "BattleMode.h"

#include "Player.h"
#include "Field.h"
#include "SoundManager.h"
#include "IRenderer.h"
#include "Screen.h"
#include "Bullet.h"

#include "DirectionalLightDesc.h"
#include "UIImageObject.h"
#include "PlayerSettingDesc.h"
#include <unordered_map>

///Sequence
#include "GameMainCountdown.h"
#include "GameMainBattle.h"
#include "GameMainGameSet.h"

BattleMode::BattleMode() :
	mObjManager(),
	mPlayableCharacterManager(),
	mColliderManager(),
	mSequencer(),
	mIsEnd(false)
{
	//プレイヤー番号を初期位置に変換するマップ、とりあえず二人分
	std::unordered_map<int, Vector3> indexToPosition;
	indexToPosition[EPlayerIndex::ONE] = Vector3(0, 5, -5);
	indexToPosition[EPlayerIndex::TWO] = Vector3(0, 5, 5);

	//プレイヤー数分ループ
	for (int i = 0; i < GameDef::PLAYER_COUNT; i++)
	{
		//プレイヤー設定
		PlayerSettingDesc desc;
		desc.mIndex = static_cast<EPlayerIndex>(i);
		desc.mHP = 30;
		desc.mRadius = 0.8f;
		desc.mPosition = indexToPosition[i];
		desc.mGenerateBulletFunc = 
			[this](Bullet* b) {
			this->mCharacterManager.add(b);
			this->mColliderManager.add(b); 
		};
		//プレイヤーの生成
		Player* player = new Player(desc);
		mPlayableCharacterManager.add(player);
		mColliderManager.add(player);
	}

	//ステージモデルの生成
	Field* field = new Field();
	mObjManager.add(field);
	mColliderManager.add(field);

	//シーケンス生成
	mSequencer.add(EGameMainState::COUNTDOWN, new GameMainCountdown());
	mSequencer.add(EGameMainState::BATTLE, new GameMainBattle(&mPlayableCharacterManager));
	mSequencer.add(EGameMainState::GAMESET, new GameMainGameSet(&mPlayableCharacterManager, [this]() { this->mIsEnd = true; }));
}

BattleMode::~BattleMode()
{
	mCharacterManager.clear();
	mPlayableCharacterManager.clear();
}

void BattleMode::init()
{
	SoundManager::instance().play(SoundID::BGM, true);

	mColliderManager.init();
	mPlayableCharacterManager.init();
	mSequencer.initState(EGameMainState::COUNTDOWN);
	mIsEnd = false;
}

void BattleMode::update(IInput & input)
{
	mSequencer.update(input);
}

void BattleMode::fixedUpdate(float dt)
{
	mCharacterManager.fixedUpdate(dt);
	mPlayableCharacterManager.fixedUpdate(dt);
	mColliderManager.collision();
	mSequencer.fixedUpdate(dt);
}

void BattleMode::lateUpdate(IInput & input)
{
	mSequencer.lateUpdate(input);
	mPlayableCharacterManager.lateUpdate(input);
}

void BattleMode::draw(IRenderer & renderer)
{
	DirectionalLightDesc light;
	light.direction = { 1, 0 ,0 };
	renderer.setDirectionalLight(light);

	mObjManager.draw(renderer);
	mCharacterManager.draw(renderer);
	mPlayableCharacterManager.draw(renderer);
	mSequencer.draw(renderer);

	//描画実行はプレイヤー(の持つカメラ)に行ってもらう
	mPlayableCharacterManager.renderExecute(renderer);
}

bool BattleMode::isEnd()
{
	return mIsEnd;
}

void BattleMode::shutdown()
{
	mCharacterManager.clear();
	SoundManager::instance().stop(SoundID::BGM);
}

EScene BattleMode::next()
{
	return EScene::TITLE;
}

/* End of File *****************************************************/