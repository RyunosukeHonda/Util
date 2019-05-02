/**
* @file TextRenderDesc.h
* @brief テキスト描画用記述子
* @author Ryunosuke Honda.
*/
#pragma once

#include "Base.h"
#include <string>

/**
*	テキスト描画用記述子構造体
*/
struct TextRenderDesc
{
public:
	/**
	*	@fn
	*	コンストラクタ
	*/
	TextRenderDesc() :
		position(0, 0),
		text(""),
		color(1, 1, 1, 1)
	{}

	//!描画位置(スクリーン座標)
	Vector2 position;
	//!描画テキスト
	string text;
	//!描画色
	D3DXCOLOR color;
};

/****** End of File *****************************************************/
