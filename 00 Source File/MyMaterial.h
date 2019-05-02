/**
* @file MyMaterial.h
* @brief オリジナルマテリアル構造体
* @author Ryunosuke Honda.
*/
#pragma once

#include "Base.h"
#include <d3d11.h>

/**
*	オリジナルマテリアル構造体
*/
struct MyMaterial
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
	MyMaterial()
	{
		ZeroMemory(this, sizeof(MyMaterial));
	}
	/**
	* @fn
	* デストラクタ
	*/
	~MyMaterial()
	{
		SAFE_RELEASE(pTexture);
	}
};

/****** End of File *****************************************************/
