/**
* @file Base.h
* @brief グローバルに使用するヘッダー、ライブラリ、マクロなどをまとめておくファイル
* @author Ryunosuke Honda.
*/
#pragma once
#pragma warning(disable : 4005)

///インクルードファイル
#include <string>
#include <stdio.h>

#include "PropertyMacro.h"
#include "MathUtility.h"
#include "Debug.h"
#include "GameDef.h"

///マクロ
#define SAFE_DELETE(p) { if(p) { delete (p); (p)=NULL; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p); (p)=NULL; } }
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }
#define MFAIL(code,string) if(FAILED( code ) ) { MessageBox(0,string,L"error",MB_OK); return E_FAIL; }
#define MFALSE(code,string) if(!( code ) ) { MessageBox(0,string,L"error",MB_OK); return E_FAIL; }
#define MSG(t) MessageBox(0,t,0,MB_OK);
#define SIZE_OF_ARRAY(array)  (sizeof(array)/sizeof((array)[0]))
#define CLAMP(x, low, high) (x > high)? high : (x < low)? low : x

using namespace std;

/**
*	全クラスに継承させておくことで必要に応じて全クラスに変数が追加できるようにする
*/
class CElement
{
};

//
//関数プロトタイプ
//

/**
* @fn
* ディレクトリ初期化
* @brief
* リソース読み込みを簡潔にするための関数に使用する
* ルートディレクトリの設定を行う
* @param (root) ルートディレクトリ
*/
void InitDirectory(WCHAR* root);

/**
* @fn
* ルートディレクトリに設定
*/
void SetRootDirectory();

/**
* @fn
* データディレクトリに設定
*/
void SetDataDirectory();

/**
* @fn
* ビジュアル(モデル、テクスチャなど)ディレクトリ設定
*/
void SetVisualDirectory();

/**
* @fn
* シェーダーディレクトリに設定
*/
void SetShaderDirectory();

/**
* @fn
* サウンドディレクトリに設定
*/
void SetSoundDirectory();

/****** End of File *****************************************************/