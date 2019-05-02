/**
* @file OBJStaticMeshLoader.h
* @brief OBJ形式スタティックメッシュ読み込みクラス定義ファイル
* @author Ryunosuke Honda.
*/
#pragma once

#include "Loader.h"

class IRenderer;

/**
*	OBJ形式スタティックメッシュ読み込みクラス
*/
class OBJStaticMeshLoader : public Loader<LPSTR>
{
public:
	/**
	* @fn
	* コンストラクタ
	* @param (renderer) レンダラー
	* @param (data) ファイル名コンテナ
	*/
	OBJStaticMeshLoader(IRenderer& renderer, FileNameContainer<LPSTR>& data);

	// Loader を介して継承されました
	virtual void update() override;

private:
	//!レンダラー
	IRenderer& mRenderer;
};

/* End of File *****************************************************/