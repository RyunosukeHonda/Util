/**
* @file IGameMainState.h
* @brief �Q�[�����C����ԃC���^�[�t�F�[�X
* @author Ryunosuke Honda.
*/
#pragma once

#include "IState.h"
#include "EGameMainState.h"

class IInput;
class IRenderer;

/**
*	�Q�[�����C����ԃC���^�[�t�F�[�X
*/
class IGameMainState : public IState<EGameMainState>
{
public:
	/**
	 * @fn
	 * ���z�f�X�g���N�^
	 */
	virtual ~IGameMainState() {}

	/**
	* @fn
	* �X�V
	* @param (input) ���̓C���^�[�t�F�[�X
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
	*/
	virtual void lateUpdate(IInput& input) = 0;

	/**
	* @fn
	* �`��
	* @param (renderer) �����_���[
	*/
	virtual void draw(IRenderer& renderer) = 0;
};

/* End of File *****************************************************/