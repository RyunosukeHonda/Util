/**
* @file ShaderTextureLoader.h
* @brief シェーダーテクスチャ(矩形に貼り付ける)読み込みクラス定義ファイル
* @author Ryunosuke Honda.
*/
#pragma once

#include "Loader.h"

class IRenderer;

/**
*	シェーダーテクスチャ(矩形に貼り付ける)読み込みクラス
*/
class ShaderTextureLoader : public Loader<LPCWSTR>
{
public:
	/**
	* @fn
	* コンストラクタ
	* @param (renderer) レンダラー
	* @param (data) ファイル名コンテナ
	*/
	ShaderTextureLoader(IRenderer& renderer, FileNameContainer<LPCWSTR>& data);

	/**
	 * @fn
	 * デストラクタ
	 */
	~ShaderTextureLoader();

	// Loader を介して継承されました
	virtual void update() override;

private:
	//!レンダラー
	IRenderer& mRenderer;
};

/* End of File *****************************************************/