/**
* @file PlayerGameSet.h
* @brief �v���C���[������ԃN���X��`�t�@�C��
* @author Ryunosuke Honda.
*/
#pragma once

#include "IPlayerState.h"
#include "EPlayerIndex.h"
#include "UIAppearingImage.h"

class Player;

/**
*	�v���C���[������ԃN���X
*	������̉��o�p
*/
class PlayerGameSet : public IPlayerState
{
public:
	/**
	* @fn
	* �R���X�g���N�^
	* @param (pPlayer) �v���C���[�|�C���^
	*/
	PlayerGameSet(Player* pPlayer);

	/**
	 * @fn
	 * �f�X�g���N�^
	 */
	~PlayerGameSet();

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
	//!�v���C���[���
	Player* mpPlayer;
	//!���X�Ɍ����摜�G�t�F�N�g
	UIAppearingImage mResultImage;
};

/* End of File *****************************************************/