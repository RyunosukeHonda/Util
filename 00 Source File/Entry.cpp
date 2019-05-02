/**
* @file Entry.cpp
* @brief エントリーポイント作成
* @author Ryunosuke Honda.
*/
///警告非表示
#pragma warning(disable : 4018)

#include <windows.h>
#include "Director.h"

///デバッグ時のみコンソール表示
#ifdef _DEBUG
#include "DebugConsole.h"
#endif

///必要なライブラリファイルのロード
#pragma comment(lib,"winmm.lib")

#pragma comment(lib,"wininet.lib")

#pragma comment(lib,"d3dx10.lib")
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dx11.lib")
#pragma comment(lib,"d3dCompiler.lib")

//#pragma comment(lib,"libfbxsdk.lib")
//#pragma comment(lib,"libfbxsdk-md.lib")
#pragma comment(lib,"libfbxsdk-mt.lib")

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, INT)
{
#ifdef _DEBUG
	DebugConsole console;
#endif
	Director* pDirector = new Director;
	if (pDirector == NULL)
	{
		MessageBox(0, L"クラス生成失敗　アプリを終了します", NULL, MB_OK);
		return 0;
	}
	//進行はディレクターに
	pDirector->Run(hInstance);

	//アプリ終了
	delete pDirector;

	return 0;
}

/****** End of File *****************************************************/