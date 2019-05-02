/**
* @file Title.cpp
* @brief タイトルシーン実装ファイル
* @author Ryunosuke Honda.
*/

#include "Title.h"

#include "IInput.h"
#include "IRenderer.h"

#include "DirectionalLightDesc.h"
#include "Screen.h"
#include "UIQuadObject.h"
#include "UIImageObject.h"
#include "UIFlashingImage.h"

///State
#include "TitleFadeIn.h"
#include "TitleIdling.h"
#include "TitleFadeOut.h"

Title::Title() :
	mObjectManager(),
	mCamera(),
	mIsEnd(false),
	mTitleSequencer()
{
	mTitleSequencer.add(ETitleState::FADEIN, new TitleFadeIn());
	mTitleSequencer.add(ETitleState::IDLING, new TitleIdling());
	mTitleSequencer.add(ETitleState::FADEOUT, new TitleFadeOut([this]() {this->mIsEnd = true; }));

	//ビューポートの設定
	D3D11_VIEWPORT vp;
	vp.Width = Screen::WINDOW_WIDTH;
	vp.Height = Screen::WINDOW_HEIGHT;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	mCamera.Viewport = vp;

	//ゲームロゴ作成
	UIImageObject* image = new UIImageObject(TextureID::GAME_LOGO);
	image->Position = { 0, 100 };
	image->Scale = { 1100, 200 };
	image->SortingLayer = 0;
	image->setColor(Color4(0, 0, 0, 0.9f));
	mObjectManager.add(image);

	//プレススタートボタン...作成
	UIFlashingImage* flash = new UIFlashingImage(TextureID::PRESS_START_BUTTON, 1.0f);
	flash->Position = { 0, -200 };
	flash->Scale = { 800, 80 };
	flash->SortingLayer = 0;
	flash->setColor(Color4(0, 0, 0, 0.9f));
	mObjectManager.add(flash);

	//背景作成
	UIQuadObject* bg = new UIQuadObject(ShaderTextureID::TITLE_BG);
	bg->Position = { 0, 0 };
	bg->Scale = { (float)Screen::WINDOW_WIDTH, (float)Screen::WINDOW_HEIGHT };
	bg->SortingLayer = -1;
	mObjectManager.add(bg);
}

Title::~Title()
{
	mObjectManager.clear();
}

void Title::init()
{
	mCamera.LocalPosition = { 0, 0, -10 };
	mCamera.LookPt = { 0, 0, 0 };
	mCamera.UpVec = { 0, 1, 0 };

	mTitleSequencer.initState(ETitleState::FADEIN);
	mIsEnd = false;
}

void Title::update(IInput& input)
{
	mTitleSequencer.update(input);
	mCamera.update();
}

void Title::fixedUpdate(float dt)
{
}

void Title::lateUpdate(IInput& input)
{
}

void Title::draw(IRenderer& renderer)
{
	DirectionalLightDesc light;
	light.direction = { 0, 1 ,0 };

	renderer.setDirectionalLight(light);
	renderer.setRenderCamera(&mCamera);

	mObjectManager.draw(renderer);
	mTitleSequencer.draw(renderer);

	renderer.renderExecute();
}

bool Title::isEnd()
{
	return mIsEnd;
}

void Title::shutdown()
{
}

EScene Title::next()
{
	return EScene::GAME_MAIN;
}

/****** End of File *****************************************************/
