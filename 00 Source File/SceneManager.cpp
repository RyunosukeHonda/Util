/**
* @file SceneManager.cpp
* @brief シーン管理クラス実装ファイル
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
	//入力情報取得
	input.update();

	//シーン更新
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

	//入力情報保存
	input.lateUpdate();
}

void SceneManager::draw(IRenderer& renderer)
{
	//画面のクリア
	renderer.clear();

	//シーン描画
	mCurrentState->draw(renderer);

	renderer.renderUI();

	//画面バッファ更新
	renderer.present();
}


/****** End of File *****************************************************/
