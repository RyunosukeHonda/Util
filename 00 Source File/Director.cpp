/**
* @file Director.cpp
* @brief ディレクタークラス実装ファイル
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
	// メッセージループ
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
	//現在シーンの更新
	mSceneManager.update(mpGameDevice->input());
	//FPS修正・fixedUpdate
	FixFPS();
	//現在シーンの更新
	mSceneManager.lateUpdate(mpGameDevice->input());
	//現在シーンの描画
	mSceneManager.draw(mpGameDevice->renderer());
}

HRESULT Director::Init()
{
	//ウィンドウ作成
	MFAIL(mWindow.InitWindow(mInstance, 0, 0, APP_NAME), L"ウィンドウ作成失敗");

	//ゲームデバイスの生成
	mpGameDevice = new GameDevice(mWindow.getWnd());

	//シーンの追加
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
		///Time ≒ 16.7~19.0なので1000で割った時間を偏差時間として送る
		mSceneManager.fixedUpdate(Time / 1000.0f);
		PreviousTime = CurrentTime;
	}
}

/****** End of File *****************************************************/
