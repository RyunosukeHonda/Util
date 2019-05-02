/**
* @file Load.cpp
* @brief ���[�h�V�[���N���X�����t�@�C��
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
	///�ǂݍ��ރ��\�[�X�̃t�@�C�������`�����Ƃɂ܂Ƃ߂�
	///�e�`����ID�񋓌^�Ə��Ԃ����킹��K�v������܂�

	mTexture = {
		L"loading.png",	//�T���v���摜
		L"GameLogo.png",	//�Q�[���^�C�g�����S�摜
		L"PressStartButton.png",	//�X�^�[�g�{�^���������ĂˁA�摜
		L"Marker.png",	//�Q�[�����C����ʂ̃^�[�Q�b�g�}�[�J�[
		L"one.png",	//1
		L"two.png",	//2
		L"three.png",	//3
		L"start.png",	//START!!
		L"win.png",	//YouWin!!
		L"lose.png",	//YouLose...
	};

	mSounds = {
		"bgm.wav",	//BGM
		"fire.wav",		//�e��
		"hit.wav",	//����
		"gameover.wav"	//�Q�[���I�[�o�[
	};

	mOBJMesh = {
		"field.obj",	//�X�e�[�W���f��
		"shot.obj"		//�e�e���f��
	};

	mFBXHierarchyMesh = {
		"tank_tex_anim.fbx"	//��Ԃ̃��f��
	};

	mFBXSkinMesh = {
		"hito.fbx",	//�v���C���[���f��
		"buyobuyo.fbx"	//�G�l�~�[���f��
	};

	mShaderTexture = {
		L"FillMonochrome.hlsl",	//�P�F�h��Ԃ��V�F�[�_�[�A�t�F�[�h�Ɏg�p
		L"TitleBG.hlsl",	//�^�C�g���w�i
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
