/**
* @file Director.h
* @brief �G���g���[�|�C���g����Ăяo����e�@�\�̏������Ȃǂ��s��
* @author Ryunosuke Honda.
*/
#pragma once

#include "Base.h"
#include "Window.h"
#include "EScene.h"
#include "SceneManager.h"

class IGameDevice;

#define APP_NAME L"game 3D action"

/**
*	�f�B���N�^�[�N���X
*/
class Director : public CElement
{
public:
	/**
	* @fn
	* �R���X�g���N�^
	*/
	Director();

	/**
	* @fn
	* �f�X�g���N�^
	*/
	~Director();

	/**
	* @fn
	* ���s���\�b�h
	* @brief �G���g���[�|�C���g����Ăяo��
	*/
	void Run(HINSTANCE);

private:
	/**
	* @fn
	* ������
	*/
	HRESULT Init();

	/**
	* @fn
	* ���C�����[�v
	*/
	void MainLoop();

	/**
	* @fn
	* FPS����
	*/
	void FixFPS();

private:
	//!�t���[�����[�g(�萔)
	static const float FRAME_RATE;

	HINSTANCE mInstance;
	//!�E�B���h�E�N���X
	Window mWindow;
	//!�Q�[���f�o�C�X�N���X����C���^�[�t�F�[�X
	IGameDevice* mpGameDevice;
	//!�V�[���Ǘ��N���X�E�Q�[�����C�������͂�����ɔC����
	SceneManager mSceneManager;
};

/****** End of File *****************************************************/