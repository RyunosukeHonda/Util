/**
* @file MySkinMaterial.h
* @brief スキンメッシュ用マテリアル構造体
* @author Ryunosuke Honda.
*/
#pragma once

#include "Base.h"

/**
*	スキンメッシュ用マテリアル構造体
*/
struct MySkinMaterial
{
	//!マテリアル名
	CHAR szName[100];
	//!アンビエント
	Color4 Ka;
	//!ディフューズ
	Color4 Kd;
	//!スペキュラー
	Color4 Ks;
	//!テクスチャーファイル名
	CHAR szTextureName[100];
	//!テクスチャのポインタ
	ID3D11ShaderResourceView* pTexture;
	//!そのマテリアルであるポリゴン数
	DWORD dwNumFace;

	/**
	* @fn
	* コンストラクタ
	*/
	MySkinMaterial()
	{
		ZeroMemory(this, sizeof(MySkinMaterial));
	}
	/**
	* @fn
	* コンストラクタ
	*/
	~MySkinMaterial()
	{
		SAFE_RELEASE(pTexture);
	}
};

/****** End of File *****************************************************/
