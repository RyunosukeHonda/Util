/**
* @file ShaderTextureID.h
* @brief シェーダーで表現するエフェクト用テクスチャの管理ID列挙型
* @author Ryunosuke Honda.
*/
#pragma once

/**
* @enum ShaderTextureID
* シェーダーで表現するエフェクト用テクスチャの管理ID列挙型
*/
enum ShaderTextureID : unsigned int
{
	//!フェード用、単色シェーダー
	MONOCHROME = 0,
	//!タイトル背景
	TITLE_BG,
};

/****** End of File *****************************************************/
