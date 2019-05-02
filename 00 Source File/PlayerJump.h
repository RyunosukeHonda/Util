///**
//* @file PlayerJump.h
//* @brief �v���C���[�W�����v��ԃN���X��`�t�@�C��
//* @author Ryunosuke Honda.
//*/
//#pragma once
//
//#include "IPlayerState.h"
//
//class Player;
//
///**
//*	�v���C���[�W�����v��ԃN���X
//*/
//class PlayerJump : public IPlayerState
//{
//	///�萔
//private:
//	//!�ړ����x
//	static const float MOVE_SPEED;
//
//public:
//	/**
//	 * @fn
//	 * �f�t�H���g�R���X�g���N�^
//	 */
//	PlayerJump(Player* pPlayer);
//
//	/**
//	 * @fn
//	 * �f�X�g���N�^
//	 */
//	~PlayerJump();
//
//	// IPlayerState ����Čp������܂���
//	virtual void init() override;
//	virtual void shutdown() override;
//	virtual bool isEnd() override;
//	virtual EPlayerState next() override;
//	virtual void update(IInput & input) override;
//	virtual void fixedUpdate(float dt) override;
//	virtual void lateUpdate(IInput & input) override;
//	virtual void draw(IRenderer & renderer) override;
//	virtual void onCollisionEnter(ACollider * other) override;
//
//private:
//	//!�I���t���O
//	bool mIsEnd;
//	//!�g�����X�t�H�[�����
//	Player* mpPlayer;
//	//!�ړ��ʕۑ��E���͂��󂯎��̂�update�����ړ��������̂�fixedUpdate(float dt)�ōs�����ߕۑ����K�v
//	Vector2 mMoveAmount;
//};
//
///* End of File *****************************************************/