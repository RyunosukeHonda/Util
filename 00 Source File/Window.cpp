/**
* @file Window.cpp
* @brief アプリケーションのウィンドウを生成するクラス実装ファイル
* @author Ryunosuke Honda.
*/
#include "Window.h"
#include "Screen.h"

///グローバル関数

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

LRESULT MsgProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);//

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return MsgProc(hWnd, uMsg, wParam, lParam);
}

LRESULT MsgProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch (iMsg)
	{
	case WM_KEYDOWN:
		switch ((char)wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, iMsg, wParam, lParam);
}

HRESULT Window::InitWindow(HINSTANCE hInstance,
	INT iX, INT iY, LPCWSTR WindowName)
{
	// ウィンドウの定義
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(wc));
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	wc.lpszClassName = WindowName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&wc);

	//ウィンドウの作成
	mWnd = CreateWindow(WindowName, WindowName, WS_OVERLAPPEDWINDOW,
		0, 0, Screen::WINDOW_WIDTH, Screen::WINDOW_HEIGHT, 0, 0, hInstance, 0);
	if (!mWnd)
	{
		return E_FAIL;
	}

	//ウインドウの表示
	ShowWindow(mWnd, SW_SHOW);
	UpdateWindow(mWnd);

	return S_OK;
}

/****** End of File *****************************************************/