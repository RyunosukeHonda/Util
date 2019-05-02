/**
* @file Title.h
* @brief �^�C�g���V�[����`�t�@�C��
* @author Ryunosuke Honda.
*/
#pragma once

#include "IScene.h"
#include "ObjectManager.h"
#include "Camera.h"
#include "TitleSequencer.h"

/**
*	�^�C�g���V�[��
*/
class Title : public IScene
{
public:
	/**
	* @fn
	* �f�t�H���g�R���X�g���N�^
	*/
	Title();

	/**
	* @fn
	* �f�X�g���N�^
	*/
	~Title();

	// IScene ����Čp������܂���
	virtual void init() override;
	virtual void update(IInput& input) override;
	virtual void fixedUpdate(float dt) override;
	virtual void lateUpdate(IInput& input) override;
	virtual void draw(IRenderer& renderer) override;
	virtual bool isEnd() override;
	virtual void shutdown() override;
	virtual EScene next() override;

private:
	//!�`��p�I�u�W�F�N�g�Ǘ��N���X�E�L�����N�^�[�͎g��Ȃ��̂ł�����ŏ\��
	ObjectManager mObjectManager;
	//!�J�����E���ɋ@�\�͕K�v�Ȃ�
	Camera mCamera;
	//!�I���t���O
	bool mIsEnd;
	//!�^�C�g���V�[�P���T�[�N���X
	TitleSequencer mTitleSequencer;
};

/****** End of File *****************************************************/