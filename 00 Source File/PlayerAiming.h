/**
* @file PlayerAiming.h
* @brief �v���C���[�G�C�~���O(�_�����߂Ă���)��ԃN���X��`�t�@�C��
* @author Ryunosuke Honda.
*/
#pragma once

#include "IPlayerState.h"

class Player;

/**
*	�v���C���[�G�C�~���O(�_�����߂Ă���)��ԃN���X��`�t�@�C��
*/
class PlayerAiming : public IPlayerState
{
	///�萔
private:
	//!�ړ����x
	static const float MOVE_SPEED;
	//!�J������]���x
	static const float CAMERA_ROTATE_SPEED;

public:
	/**
	* @fn
	* �R���X�g���N�^
	* @param (pPlayer) �v���C���[�|�C���^
	*/
	PlayerAiming(Player* pPlayer);

	/**
	 * @fn
	 * �f�X�g���N�^
	 */
	~PlayerAiming();

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
	virtual void gameSet() override;

private:
	//!�I���t���O
	bool mIsEnd;
	//!���̈ړ���X�e�[�g
	EPlayerState mNext;
	//!�g�����X�t�H�[�����
	Player* mpPlayer;
	//!�ړ��ʕۑ��E���͂��󂯎��̂�update�����ړ��������̂�fixedUpdate�ōs�����ߕۑ����K�v
	Vector2 mMoveAmount;
	//!�������J������]�ʕۑ�
	Vector2 mCameraRotateAmount;
};

/* End of File *****************************************************/