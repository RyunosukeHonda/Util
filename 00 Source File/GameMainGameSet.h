/**
* @file GameMainGameSet.h
* @brief �Q�[�����C���V�[����ԁE�����N���X��`�t�@�C��
* @author Ryunosuke Honda.
*/
#pragma once

#include "IGameMainState.h"
#include "Timer.h"
#include <functional>

class PlayableCharacterManager;

/**
*	�Q�[�����C���V�[����ԁE�����N���X
*	�������o��A�^�C�g����ʂɖ߂�
*/
class GameMainGameSet : public IGameMainState
{
public:
	/**
	 * @fn
	 * �R���X�g���N�^
	 */
	GameMainGameSet(PlayableCharacterManager* pcManager, std::function<void()> endFunc);
	
	/**
	 * @fn
	 * �f�X�g���N�^
	 */
	~GameMainGameSet();

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
	//!�Q�[���I����ʒm����֐�
	std::function<void()> mEndFunc;
	//!�I���܂ł̎��ԊԊu�p�^�C�}�[
	Timer mTimer;
	//!�v���C���[�Ǘ��N���X�E���ɏ�ʂŐ����������̂��g�p���邽�߃|�C���^�ϐ��ŕێ�
	PlayableCharacterManager* mpPlayableCharacterManager;
};

/* End of File *****************************************************/