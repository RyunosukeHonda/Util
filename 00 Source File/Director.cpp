/**
* @file Director.cpp
* @brief �f�B���N�^�[�N���X�����t�@�C��
* @author Ryunosuke Honda.
*/
#include "Director.h"

#include "GameDevice.h"
#include "Load.h"
#include "Title.h"
#include "BattleMode.h"

const float Director::FRAME_RATE = 60.0f;

Director::Director() :
	mInstance(),
	mWindow(),
	mpGameDevice(nullptr),
	mSceneManager()
{
}

Director::~Director()
{
	delete mpGameDevice;
}

void Director::Run(HINSTANCE hInstance)
{
	WCHAR dir[1024];
	GetCurrentDirectory(sizeof(dir), dir);
	InitDirectory(dir);

	mInstance = hInstance;
	if (FAILED(Init()))
	{
		return;
	}
	ShowWindow(mWindow.Wnd, SW_SHOW);
	UpdateWindow(mWindow.Wnd);
	// ���b�Z�[�W���[�v
	MSG msg = { 0 };
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			MainLoop();
		}
	}
}

void Director::MainLoop()
{
	//���݃V�[���̍X�V
	mSceneManager.update(mpGameDevice->input());
	//FPS�C���EfixedUpdate
	FixFPS();
	//���݃V�[���̍X�V
	mSceneManager.lateUpdate(mpGameDevice->input());
	//���݃V�[���̕`��
	mSceneManager.draw(mpGameDevice->renderer());
}

HRESULT Director::Init()
{
	//�E�B���h�E�쐬
	MFAIL(mWindow.InitWindow(mInstance, 0, 0, APP_NAME), L"�E�B���h�E�쐬���s");

	//�Q�[���f�o�C�X�̐���
	mpGameDevice = new GameDevice(mWindow.getWnd());

	//�V�[���̒ǉ�
	mSceneManager.add(EScene::LOAD, new Load(mpGameDevice));
	mSceneManager.add(EScene::TITLE, new Title);
	mSceneManager.add(EScene::GAME_MAIN, new BattleMode);
	mSceneManager.initState(EScene::LOAD);

	return S_OK;
}

void Director::FixFPS()
{
	static LARGE_INTEGER Frq = { 0 }, PreviousTime = { 0 }, CurrentTime = { 0 };
	DOUBLE Time = 0;

	QueryPerformanceFrequency(&Frq);
	QueryPerformanceCounter(&CurrentTime);
	Time = CurrentTime.QuadPart - PreviousTime.QuadPart;
	Time *= (DOUBLE)1000.0 / (DOUBLE)Frq.QuadPart;

	if (Time > 1000.0f / FRAME_RATE)
	{
		///Time �� 16.7~19.0�Ȃ̂�1000�Ŋ��������Ԃ�΍����ԂƂ��đ���
		mSceneManager.fixedUpdate(Time / 1000.0f);
		PreviousTime = CurrentTime;
	}
}

/****** End of File *****************************************************/
