/**
* @file Debug.h
* @brief デバッグ時のみ使用する汎用関数まとめクラス
* @author Ryunosuke Honda.
*/
#pragma once

#include <iostream>
#include <string>

using namespace std;

#if _DEBUG
/**
* @def PRINT
* 引数の中身を簡単に出力するマクロ
* @param (var) 中身を知りたい変数
*/
#define PRINT(var) std::cout<<#var"= "<<var<<std::endl

/**
*	デバッグ時のみ使用する汎用関数まとめクラス
*/
class Debug
{
public:
	static void log(const char* mes)
	{
		cout << mes << endl;
	}

	static void log(string& mes)
	{
		cout << mes << endl;
	}

	static void messageBox(LPCWSTR mes)
	{
		MessageBox(0, mes, NULL, MB_OK);
	}
};

#else

#define PRINT(var) 
/**
*	リリース時はこちら
*	内部処理のない同名関数を羅列しておくことで
*	デバッグエラーを防止する
*/
class Debug
{
public:
	///FIXME リリース用関数
	static void log(const char* mes) {}
	static void log(string& mes) {}
	static void messageBox(LPCWSTR mes) {}
};


#endif

/* End of File *****************************************************/