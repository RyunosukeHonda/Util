/**
* @file BattleMode.cpp
* @brief �o�g�����[�h�V�[���N���X�����t�@�C��
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
	//�v���C���[�ԍ��������ʒu�ɕϊ�����}�b�v�A�Ƃ肠������l��
	std::unordered_map<int, Vector3> indexToPosition;
	indexToPosition[EPlayerIndex::ONE] = Vector3(0, 5, -5);
	indexToPosition[EPlayerIndex::TWO] = Vector3(0, 5, 5);

	//�v���C���[�������[�v
	for (int i = 0; i < GameDef::PLAYER_COUNT; i++)
	{
		//�v���C���[�ݒ�
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
		//�v���C���[�̐���
		Player* player = new Player(desc);
		mPlayableCharacterManager.add(player);
		mColliderManager.add(player);
	}

	//�X�e�[�W���f���̐���
	Field* field = new Field();
	mObjManager.add(field);
	mColliderManager.add(field);

	//�V�[�P���X����
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

	//�`����s�̓v���C���[(�̎��J����)�ɍs���Ă��炤
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