/**
* @file IScene.h
* @brief �V�[���C���^�[�t�F�[�X��`�t�@�C��
* @author Ryunosuke Honda.
*/
#pragma once

#include "IState.h"
#include "EScene.h"

class IInput;
class IRenderer;

/**
*	�V�[���C���^�[�t�F�[�X
*/
class IScene : public IState<EScene>
{
public:
	/**
	* @fn
	* ���z�f�X�g���N�^
	*/
	virtual ~IScene(){}

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

/****** EOF *****************************************************/
