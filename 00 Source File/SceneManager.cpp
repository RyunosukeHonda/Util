/**
* @file SceneManager.cpp
* @brief �V�[���Ǘ��N���X�����t�@�C��
* @author Ryunosuke Honda.
*/
#include "SceneManager.h"

#include "IInput.h"
#include "IRenderer.h"

SceneManager::SceneManager()
{
}

void SceneManager::update(IInput& input)
{
	//���͏��擾
	input.update();

	//�V�[���X�V
	mCurrentState->update(input);
}

void SceneManager::fixedUpdate(float dt)
{
	mCurrentState->fixedUpdate(dt);
}

void SceneManager::lateUpdate(IInput & input)
{
	mCurrentState->lateUpdate(input);

	stateEndCheck();

	//���͏��ۑ�
	input.lateUpdate();
}

void SceneManager::draw(IRenderer& renderer)
{
	//��ʂ̃N���A
	renderer.clear();

	//�V�[���`��
	mCurrentState->draw(renderer);

	renderer.renderUI();

	//��ʃo�b�t�@�X�V
	renderer.present();
}


/****** End of File *****************************************************/
