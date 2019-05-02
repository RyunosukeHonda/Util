/**
* @file Screen.h
* @brief スクリーンサイズ実装ファイル
* @author Ryunosuke Honda.
*/
#include "Screen.h"
#include "Base.h"

///static float の初期化がヘッダー内で行えないためcppにて実装

float Screen::FOV = (float)D3DX_PI / 8.0f;
float Screen::NEAR_ = 0.1f;
float Screen::FAR_ = 1000.0f;

/****** End of File *****************************************************/
