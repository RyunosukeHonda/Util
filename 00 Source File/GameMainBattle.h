/**
* @file GameMainBattle.h
* @brief �Q�[�����C���V�[����ԁE�o�g���N���X��`�t�@�C��
* @author Ryunosuke Honda.
*/
#pragma once

#include "IGameMainState.h"
#include "ObjectManager.h"

class PlayableCharacterManager;

/**
*	�Q�[�����C���V�[����ԁE�o�g���N���X
*	�o�g�����s�킹��A������̃��C���V�[��
*/
class GameMainBattle : public IGameMainState
{
public:
	/**
	 * @fn
	 * �R���X�g���N�^
	 */
	GameMainBattle(PlayableCharacterManager* pcManager);

	/**
	 * @fn
	 * �f�X�g���N�^
	 */
	~GameMainBattle();

	// IGameMainState ����Čp������܂���
	virtual void init() override;
	virtual void shutdown() override;
	virtual bool isEnd() override;
	virtual EGameMainState next() override;
	virtual void update(IInput & input) override;
	virtual void fixedUpdate(float dt) override;
	virtual void lateUpdate(IInput & input) override;
	virtual void draw(IRenderer & renderer) override;

private:
	//!�v���C���[�Ǘ��N���X�E���ɏ�ʂŐ����������̂��g�p���邽�߃|�C���^�ϐ��ŕێ�
	PlayableCharacterManager* mpPlayableCharacterManager;
	//!�X�V�̕K�v�̂Ȃ��I�u�W�F�N�g�̊Ǘ��N���X�EUI�Ȃǂ̕`��p
	ObjectManager mObjManager;
};

/* End of File *****************************************************/