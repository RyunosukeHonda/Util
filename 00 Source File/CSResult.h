/**
* @file CSResult
* @brief コンピュートシェーダーからの衝突結果受け取り用の構造体
* @author Ryunosuke Honda.
*/
#pragma once

/**
*	コンピュートシェーダーからの衝突結果受け取り用の構造体
*/
struct CSResult
{
	//!結果の格納に使用、1=true、0=false
	int Hit;
};

/****** End of File *****************************************************/
