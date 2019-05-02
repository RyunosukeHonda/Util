/**
* @file Load.h
* @brief ロードシーンクラス定義ファイル
* @author Ryunosuke Honda.
*/
#pragma once

#include "IScene.h"
#include "TextureLoader.h"
#include "SoundLoader.h"
#include "OBJStaticMeshLoader.h"
#include "FBXHierarchyMeshLoader.h"
#include "FBXSkinMeshLoader.h"
#include "ShaderTextureLoader.h"
#include "UIImageObject.h"

class IGameDevice;

/**
*	ロードシーンクラス
*/
class Load : public IScene
{
public:
	/**
	* @fn
	* コンストラクタ
	* @param (device) ゲームデバイスインターフェース
	*/
	Load(IGameDevice* device);
	virtual ~Load();

	// IScene を介して継承されました
	virtual void init() override;
	virtual void update(IInput& input) override;
	virtual void fixedUpdate(float dt) override;
	virtual void lateUpdate(IInput& input) override;
	virtual void draw(IRenderer & renderer) override;
	virtual void shutdown() override;
	virtual bool isEnd() override;
	virtual EScene next() override;

private:
	//!終了したか
	bool isEndFlag;

	//!テクスチャファイル名リスト
	FileNameContainer<LPCWSTR> mTexture;
	//!テクスチャ読み込みクラス
	TextureLoader mTextureLoader;

	//!サウンドファイル名リスト
	FileNameContainer<LPSTR> mSounds;
	//!サウンド読み込みクラス
	SoundLoader mSoundLoader;

	//!OBJメッシュファイル名リスト
	FileNameContainer<LPSTR> mOBJMesh;
	//!OBJメッシュ読み込みクラス
	OBJStaticMeshLoader mOBJMeshLoader;

	//!FBX階層メッシュファイル名リスト
	FileNameContainer<LPSTR> mFBXHierarchyMesh;
	//!FBX階層メッシュ読み込みクラス
	FBXHierarchyMeshLoader mFBXHierarchyMeshLoader;

	//!FBXスキンメッシュファイル名リスト
	FileNameContainer<LPSTR> mFBXSkinMesh;
	//!FBXスキンメッシュ読み込みクラス
	FBXSkinMeshLoader mFBXSkinMeshLoader;

	//!シェーダーテクスチャファイル名リスト
	FileNameContainer<LPCWSTR> mShaderTexture;
	//!シェーダーテクスチャ読み込みクラス
	ShaderTextureLoader mShaderTextureLoader;

	//!NowLoading...
	UIImageObject mLoading;
};
