/**
* @file TextureLoader.h
* @brief テクスチャ(スプライト用画像)読み込みクラス定義ファイル
* @author Ryunosuke Honda.
*/
#pragma once

#include "Loader.h"

class IRenderer;

/**
*	テクスチャ読み込みクラス
*	四角形ポリゴンに貼り付ける画像を読み込む
*/
class TextureLoader : public Loader<LPCWSTR>
{
public:
	/**
	* @fn
	* コンストラクタ
	* @param (renderer) レンダラー
	* @param (data) ファイル名コンテナ
	*/
	TextureLoader(IRenderer& renderer, FileNameContainer<LPCWSTR>& data);

	// Loader を介して継承されました
	virtual void update() override;

private:
	//!レンダラー
	IRenderer& mRenderer;
};

/****** End of File *****************************************************/