/**
* @file IPlayerState.h
* @brief �v���C���[�̏�ԃC���^�[�t�F�[�X
* @author Ryunosuke Honda.
*/
#pragma once

#include "Base.h"
#include "IState.h"
#include "EPlayerState.h"

class IInput;
class IRenderer;
class ACollider;

/**
*	�v���C���[��ԃC���^�[�t�F�[�X	
*/
class IPlayerState : public IState<EPlayerState>
{
public:
	/**
	 * @fn
	 * ���z�f�X�g���N�^
	 */
	virtual ~IPlayerState() {}

	/**
	* @fn
	* �X�V
	* @param (input) ���̓C���^�[�t�F�[�X
	* @param (sound) �T�E���h�C���^�[�t�F�[�X
	*/
	virtual void update(IInput& input) = 0;

	/**
	* @fn
	* FPS60�����X�V�E��������̏������L�q
	* @param (dt) �t���[���΍�����
	*/
	virtual void fixedUpdate(float dt) = 0;

	/**
	* @fn
	* �x���X�V�Eupdate��肠�ƂɎ��s�������������L�q
	* @param (input) ���̓C���^�[�t�F�[�X
	* @param (sound) �T�E���h�C���^�[�t�F�[�X
	*/
	virtual void lateUpdate(IInput& input) = 0;

	/**
	* @fn
	* �`��
	* @param (renderer) �����_���[
	*/
	virtual void draw(IRenderer& renderer) = 0;

	/**
	* @fn
	* �Փˎ��C�x���g
	* @param (other) �Փˑ���
	*/
	virtual void onCollisionEnter(ACollider * other) = 0;

	/**
	* @fn
	* ������Ԃɋ����ڍs����
	*/
	virtual void gameSet() = 0;
};

/* End of File *****************************************************/