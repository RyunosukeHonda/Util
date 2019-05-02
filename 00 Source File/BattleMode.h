/**
* @file BattleMode.h
* @brief �o�g�����[�h�V�[���N���X��`�t�@�C��
* @author Ryunosuke Honda.
*/
#pragma once

#include "IScene.h"

#include "ObjectManager.h"
#include "CharacterManager.h"
#include "PlayableCharacterManager.h"
#include "ColliderManager.h"
#include "GameMainSequencer.h"

/**
*	�o�g�����[�h�V�[���N���X
*/
class BattleMode : public IScene
{
public:
	/**
	 * @fn
	 * �f�t�H���g�R���X�g���N�^
	 */
	BattleMode();

	/**
	 * @fn
	 * �f�X�g���N�^
	 */
	~BattleMode();

	// IScene ����Čp������܂���
	virtual void init() override;

	virtual void update(IInput & input) override;

	virtual void fixedUpdate(float dt) override;

	virtual void lateUpdate(IInput & input) override;

	virtual void draw(IRenderer & renderer) override;

	virtual bool isEnd() override;

	virtual void shutdown() override;

	virtual EScene next() override;

private:
	//!�X�V�̕K�v�̂Ȃ��I�u�W�F�N�g�̊Ǘ��N���X
	ObjectManager mObjManager;
	//!����L�����N�^�[�Ǘ��N���X
	PlayableCharacterManager mPlayableCharacterManager;
	//!�L�����N�^�[�Ǘ��N���X
	CharacterManager mCharacterManager;
	//!�R���C�_�[�Ǘ��N���X
	ColliderManager mColliderManager;
	//!�Q�[�����C���V�[���V�[�P���T�[�N���X
	GameMainSequencer mSequencer;
	//!�V�[���I���t���O
	bool mIsEnd;
};

/* End of File *****************************************************/