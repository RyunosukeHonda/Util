/**
* @file DebugConsole.h
* @brief デバッグ用のコンソールウィンドウクラス定義ファイル
* @author Ryunosuke Honda.
*/

#pragma once

#include <wincon.h>
#include <stdlib.h>
#include <iostream>

/**
*	デバッグ用コンソールクラス
*/
class DebugConsole
{
public:
	/**
	* @fn
	* コンストラクタ
	* @brief 必要な処理も同時に行う
	*/
	DebugConsole() {
		::AllocConsole();
		freopen_s(&fp, "CON", "w", stdout);    // 標準出力の割り当て
		cout << "DebugConsole awaking..." << endl;
	}

	/**
	* @fn
	* デストラクタ
	* @brief 解放処理を行う
	*/
	~DebugConsole() {
		cout << "DebugConsole closing..." << endl;
		fclose(fp);
		::FreeConsole();
	}

private:
	//!ファイルポインタ
	FILE *fp;
};

/****** End of File *****************************************************/
