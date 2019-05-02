/**
* @file FBXHierarchyMeshLoader.h
* @brief FBX階層メッシュ読み込みクラス定義ファイル
* @author Ryunosuke Honda.
*/
#pragma once

#include "Loader.h"

class IRenderer;

/**
*	FBX階層メッシュ読み込みクラス
*/
class FBXHierarchyMeshLoader : public Loader<LPSTR>
{
public:
	/**
	* @fn
	* コンストラクタ
	* @param (renderer) レンダラー
	* @param (data) ファイル名コンテナ
	*/
	FBXHierarchyMeshLoader(IRenderer& renderer, FileNameContainer<CHAR*>& data);

	/**
	* @fn
	* デストラクタ
	*/
	~FBXHierarchyMeshLoader();

	// Loader を介して継承されました
	virtual void update() override;

private:
	//!レンダラー
	IRenderer& mRenderer;
};

/* End of File *****************************************************/