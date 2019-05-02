/**
* @file GameMainCountdown.h
* @brief �Q�[�����C���V�[����ԁE�J�E���g�_�E���N���X��`�t�@�C��
* @author Ryunosuke Honda.
*/
#pragma once

#include "IGameMainState.h"
#include "Timer.h"

#include "UIImageObject.h"
#include <memory>
#include <unordered_map>

/**
*	�Q�[�����C���V�[����ԁE�J�E���g�_�E���N���X
*	�Q�[���J�n�܂ł̃J�E���g�_�E�����s���A���̊Ԃ͑�����󂯕t���Ȃ�
*/
class GameMainCountdown : public IGameMainState
{
	///�萔
private:
	//!Start!!�̉摜�C���f�b�N�X
	static const int START = 0;
	//!�P�̉摜�C���f�b�N�X
	static const int ONE = 1;
	//!�Q�̉摜�C���f�b�N�X
	static const int TWO = 2;
	//!�R�̉摜�C���f�b�N�X
	static const int THREE = 3;

public:
	/**
	 * @fn
	 * �f�t�H���g�R���X�g���N�^
	 */
	GameMainCountdown();

	/**
	 * @fn
	 * �f�X�g���N�^
	 */
	~GameMainCountdown();

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
	//!�J�E���g�_�E���^�C�}�[
	Timer mTimer;
	//!UI�摜�|�C���^����
	using CountImagePointer = std::unique_ptr<UIImageObject>;
	//!���ԂɑΉ�����UI�摜���i�[����}�b�v����
	using CountImageMap =  std::unordered_map<int, CountImagePointer>;
	//!���ԂɑΉ�����UI�摜���i�[����}�b�v
	CountImageMap mCountImage[GameDef::PLAYER_COUNT];
};

/* End of File *****************************************************/