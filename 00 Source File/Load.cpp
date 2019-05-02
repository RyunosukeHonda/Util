/**
* @file Load.cpp
* @brief ロードシーンクラス実装ファイル
* @author Ryunosuke Honda.
*/
#include "Load.h"
#include "IGameDevice.h"

Load::Load(IGameDevice* device) :
	isEndFlag(false),
	mTexture(),
	mTextureLoader(device->renderer(), mTexture),
	mSounds(),
	mSoundLoader(mSounds),
	mOBJMesh(),
	mOBJMeshLoader(device->renderer(), mOBJMesh),
	mFBXHierarchyMesh(),
	mFBXHierarchyMeshLoader(device->renderer(), mFBXHierarchyMesh),
	mFBXSkinMesh(),
	mFBXSkinMeshLoader(device->renderer(), mFBXSkinMesh),
	mShaderTexture(),
	mShaderTextureLoader(device->renderer(), mShaderTexture),
	mLoading(TextureID::LOADDING)
{
	mLoading.Position = { 320, -300 };
	mLoading.Scale = { 600, 100 };
}

Load::~Load()
{
}

void Load::init()
{
	///読み込むリソースのファイル名を形式ごとにまとめる
	///各形式のID列挙型と順番を合わせる必要があります

	mTexture = {
		L"loading.png",	//サンプル画像
		L"GameLogo.png",	//ゲームタイトルロゴ画像
		L"PressStartButton.png",	//スタートボタンを押してね、画像
		L"Marker.png",	//ゲームメイン画面のターゲットマーカー
		L"one.png",	//1
		L"two.png",	//2
		L"three.png",	//3
		L"start.png",	//START!!
		L"win.png",	//YouWin!!
		L"lose.png",	//YouLose...
	};

	mSounds = {
		"bgm.wav",	//BGM
		"fire.wav",		//銃声
		"hit.wav",	//命中
		"gameover.wav"	//ゲームオーバー
	};

	mOBJMesh = {
		"field.obj",	//ステージモデル
		"shot.obj"		//銃弾モデル
	};

	mFBXHierarchyMesh = {
		"tank_tex_anim.fbx"	//戦車のモデル
	};

	mFBXSkinMesh = {
		"hito.fbx",	//プレイヤーモデル
		"buyobuyo.fbx"	//エネミーモデル
	};

	mShaderTexture = {
		L"FillMonochrome.hlsl",	//単色塗りつぶしシェーダー、フェードに使用
		L"TitleBG.hlsl",	//タイトル背景
	};

	isEndFlag = false;
}

void Load::update(IInput& input)
{
	if (!mTextureLoader.isEnd())
	{
		mTextureLoader.update();
	}
	else if (!mSoundLoader.isEnd())
	{
		mSoundLoader.update();
	}
	else if (!mOBJMeshLoader.isEnd())
	{
		mOBJMeshLoader.update();
	}
	else if (!mFBXHierarchyMeshLoader.isEnd())
	{
		mFBXHierarchyMeshLoader.update();
	}
	else if (!mFBXSkinMeshLoader.isEnd())
	{
		mFBXSkinMeshLoader.update();
	}
	else if (!mShaderTextureLoader.isEnd())
	{
		mShaderTextureLoader.update();
	}
	else
	{
		isEndFlag = true;
	}
}

void Load::fixedUpdate(float dt)
{
}

void Load::lateUpdate(IInput& input)
{
}

void Load::draw(IRenderer & renderer)
{
	mLoading.draw(renderer);
}

void Load::shutdown()
{
}

bool Load::isEnd()
{
	return isEndFlag;
}

EScene Load::next()
{
	return EScene::TITLE;
}
