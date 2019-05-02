/**
* @file Player.h
* @brief �v���C���[�N���X��`�t�@�C��
* @author Ryunosuke Honda.
*/
#pragma once

#include "Base.h"
#include "APlayableCharacter.h"
#include "SphereCollider.h"
#include "StateMachineTemplate.h"
#include "EPlayerState.h"
#include "IPlayerState.h"
#include "FPSCamera.h"
#include "FBXSkinMeshRenderDesc.h"
#include <memory>
#include "UIDisappearingQuad.h"
#include "EPlayerIndex.h"

struct PlayerSettingDesc;
class IShotable;

/**
*	�v���C���[�N���X
*/
class Player : 
	public APlayableCharacter, 
	public SphereCollider,
	public StateMachineTemplate<EPlayerState, IPlayerState> 
{
public:
	/**
	 * @fn
	 * �R���X�g���N�^
	 */
	Player(const PlayerSettingDesc& settingDesc);

	/**
	 * @fn
	 * �f�X�g���N�^
	 */
	~Player();

	/**
	* @fn
	* �ړ�����
	*/
	void move(const Vector2& amount);

	/**
	* @fn
	* �ړ�����
	*/
	void rotateCamera(const Vector2& amount);

	// APlayableCharacter ����Čp������܂���
	virtual void init() override;
	virtual void update(IInput& input) override;
	virtual void lateUpdate(IInput & input) override;
	virtual void fixedUpdate(float dt) override;
	virtual void draw(IRenderer & renderer) override;
	virtual void renderExecute(IRenderer & renderer) override;
	virtual void gameSet() override;
	
	// SphereCollider ����Čp������܂���
	virtual void onCollisionEnter(ACollider* other) override;
	virtual void onCollisionStay(ACollider* other) override;
	virtual void onCollisionExit(ACollider* other) override;

private:
	//!�A�j���[�V�����t���[��
	PROPERTY_READWRITE(int, Frame);
	//!FPS�J����
	FPSCamera mCamera;
	//!�ˌ��@�\�C���^�[�t�F�[�X
	unique_ptr<IShotable> mShot;
	//!�v���C���[�ԍ�
	PROPERTY_READONLY(EPlayerIndex, Index);
	//!���f���`��p�L�q�q
	FBXSkinMeshRenderDesc mDesc;
	//!���������p�ɏ����ʒu��ێ�
	Vector3 mInitPosition;
	//!�_���[�W���̃G�t�F�N�g
	UIDisappearingQuad mDamageEffect;
};

/* End of File *****************************************************/