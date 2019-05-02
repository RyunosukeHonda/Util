/**
* @file FBXSkinMeshLoader.h
* @brief FBXスキンメッシュ読み込みクラス定義ファイル
* @author Ryunosuke Honda.
*/
#pragma once

#include "Loader.h"

class IRenderer;

/**
*	FBXスキンメッシュ読み込みクラス
*/
class FBXSkinMeshLoader : public Loader<LPSTR>
{
public:
	/**
	* @fn
	* コンストラクタ
	* @param (renderer) レンダラー
	* @param (data) ファイル名コンテナ
	*/
	FBXSkinMeshLoader(IRenderer& renderer, FileNameContainer<LPSTR>& data);
	
	/**
	 * @fn
	 * デストラクタ
	 */
	~FBXSkinMeshLoader();

	// Loader を介して継承されました
	virtual void update() override;

private:
	//!レンダラー
	IRenderer& mRenderer;
};

/* End of File *****************************************************/