/**
* @file SceneManager.h
* @brief �V�[���Ǘ��N���X��`�t�@�C��
* @author Ryunosuke Honda.
*/
#pragma once

#include "EScene.h"
#include "IScene.h"
#include "Base.h"
#include "StateMachineTemplate.h"

/**
*	�V�[���Ǘ��N���X
*/
class SceneManager : public StateMachineTemplate<EScene, IScene>
{
public:
	/*
	* @fn
	* �f�t�H���g�R���X�g���N�^
	*/
	SceneManager();

	/*
	* @fn
	* �f�X�g���N�^
	*/
	~SceneManager() = default;

	/*
	* @fn
	* �V�[���X�V
	* @param (input) ���͋@�\
	* @brief ���ݎ��s���̃V�[�����X�V
	*/
	void update(IInput& input);

	/*
	* @fn
	* �V�[���X�V�EFPS60�ɋ������ꂽ����
	* @param (dt)  �t���[���̍�������
	* @brief ��ɕ�������̏�����������ōs��
	*/
	void fixedUpdate(float dt);

	/*
	* @fn
	* �V�[���x���X�V
	* @param (input) ���͋@�\
	* @brief ���̍X�V�������I��������ɏ��������X�V����
	* �V�[���J�ڂ���͏��ۊǂȂǂ��s��
	*/
	void lateUpdate(IInput& input);

	/*
	* @fn
	* �V�[���`��
	* @param (renderer)  �`��I�u�W�F�N�g
	* @brief ���ݎ��s���̃V�[����`��
	*/
	void draw(IRenderer& renderer);

private:
	/*
	* @fn
	* �R�s�[�R���X�g���N�^�i�R�s�[�֎~�j
	* @brief ����֐��̈Öْ�`�𖾎��I�ɋ֎~
	*/
	SceneManager(const SceneManager&) = delete;
	SceneManager& operator=(const SceneManager&) = delete;
};

/****** EOF *****************************************************/
