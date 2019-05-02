///**
//* @file BattlePlayer.h
//* @brief �ΐ탂�[�h�p�v���C���[�N���X��`�t�@�C��
//* Player�N���X�����Ƃ��A���l���v���C�̓��́E�`��ɑΉ��������N���X
//* @author Ryunosuke Honda.
//*/
//#pragma once
//
//#include "Player.h"
//#include "EPlayerIndex.h"
//
///**
//*	�ΐ탂�[�h�p�v���C���[�N���X
//*/
//class BattlePlayer : public Player
//{
//public:
//	/**
//	* @fn
//	* �R���X�g���N�^
//	* @param (index) �v���C���[�ԍ�
//	* @param (hp) �̗�
//	*/
//	BattlePlayer(EPlayerIndex index, int hp, IAddable<ACharacter>* characterMgr, IAddable<ACollider>* colliderMgr);
//
//	/**
//	 * @fn
//	 * �f�X�g���N�^
//	 */
//	~BattlePlayer();
//
//	virtual void init() override;
//
//	virtual void update(IInput& input) override;
//
//	virtual void onCollisionEnter(ACollider* other)override;
//
//private:
//	using base = Player;
//	//!�v���C���[�ԍ�
//	EPlayerIndex mIndex;
//};
//
///* End of File *****************************************************/