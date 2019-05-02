/**
* @file SoundLoader.h
* @brief 音リソース読み込みクラス定義ファイル
* @author Ryunosuke Honda.
*/
#pragma once

#include "Loader.h"

/**
*	音リソース読み込みクラス
*/
class SoundLoader : public Loader<LPSTR>
{
public:
	/**
	* @fn
	* コンストラクタ
	* @param (data) データ名コンテナ
	*/
	SoundLoader(FileNameContainer<LPSTR>& data);

	// Loader を介して継承されました
	virtual void update() override;
};

/****** End of File *****************************************************/