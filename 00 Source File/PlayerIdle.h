/**
* @file PlayerIdle.h
* @brief �v���C���[�ҋ@��ԃN���X��`�t�@�C��
* @author Ryunosuke Honda.
*/
#pragma once

#include "IPlayerState.h"
#include "EPlayerIndex.h"

class Player;

/**
*	�v���C���[�ҋ@��ԃN���X
*	�A�j���[�V������0�ɖ߂�
*/
class PlayerIdle : public IPlayerState
{
	///�萔
private:
	//!�J������]���x
	static const float CAMERA_ROTATE_SPEED;

public:
	/**
	* @fn
	* �R���X�g���N�^
	* @param (pPlayer) �v���C���[�|�C���^
	*/
	PlayerIdle(Player* pPlayer);

	/**
	 * @fn
	 * �f�X�g���N�^
	 */
	~PlayerIdle();

	// IPlayerState ����Čp������܂���
	virtual void init() override;
	virtual void shutdown() override;
	virtual bool isEnd() override;
	virtual EPlayerState next() override;
	virtual void update(IInput & input) override;
	virtual void fixedUpdate(float dt) override;
	virtual void lateUpdate(IInput & input) override;
	virtual void draw(IRenderer & renderer) override;
	virtual void onCollisionEnter(ACollider * other) override;

private:
	//!�I���t���O
	bool mIsEnd;
	//!���̃X�e�[�g
	EPlayerState mNext;
	//!�v���C���[���
	Player* mpPlayer;
	//!�J������]�ʕۑ��E���͂��󂯎��̂�update�����ړ��������̂�fixedUpdate�ōs�����ߕۑ����K�v
	Vector2 mCameraRotateAmount;

	// IPlayerState ����Čp������܂���
	virtual void gameSet() override;
};

/* End of File *****************************************************/