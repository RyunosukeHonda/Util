/**
* @file Load.h
* @brief ���[�h�V�[���N���X��`�t�@�C��
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
*	���[�h�V�[���N���X
*/
class Load : public IScene
{
public:
	/**
	* @fn
	* �R���X�g���N�^
	* @param (device) �Q�[���f�o�C�X�C���^�[�t�F�[�X
	*/
	Load(IGameDevice* device);
	virtual ~Load();

	// IScene ����Čp������܂���
	virtual void init() override;
	virtual void update(IInput& input) override;
	virtual void fixedUpdate(float dt) override;
	virtual void lateUpdate(IInput& input) override;
	virtual void draw(IRenderer & renderer) override;
	virtual void shutdown() override;
	virtual bool isEnd() override;
	virtual EScene next() override;

private:
	//!�I��������
	bool isEndFlag;

	//!�e�N�X�`���t�@�C�������X�g
	FileNameContainer<LPCWSTR> mTexture;
	//!�e�N�X�`���ǂݍ��݃N���X
	TextureLoader mTextureLoader;

	//!�T�E���h�t�@�C�������X�g
	FileNameContainer<LPSTR> mSounds;
	//!�T�E���h�ǂݍ��݃N���X
	SoundLoader mSoundLoader;

	//!OBJ���b�V���t�@�C�������X�g
	FileNameContainer<LPSTR> mOBJMesh;
	//!OBJ���b�V���ǂݍ��݃N���X
	OBJStaticMeshLoader mOBJMeshLoader;

	//!FBX�K�w���b�V���t�@�C�������X�g
	FileNameContainer<LPSTR> mFBXHierarchyMesh;
	//!FBX�K�w���b�V���ǂݍ��݃N���X
	FBXHierarchyMeshLoader mFBXHierarchyMeshLoader;

	//!FBX�X�L�����b�V���t�@�C�������X�g
	FileNameContainer<LPSTR> mFBXSkinMesh;
	//!FBX�X�L�����b�V���ǂݍ��݃N���X
	FBXSkinMeshLoader mFBXSkinMeshLoader;

	//!�V�F�[�_�[�e�N�X�`���t�@�C�������X�g
	FileNameContainer<LPCWSTR> mShaderTexture;
	//!�V�F�[�_�[�e�N�X�`���ǂݍ��݃N���X
	ShaderTextureLoader mShaderTextureLoader;

	//!NowLoading...
	UIImageObject mLoading;
};
