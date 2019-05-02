/**
* @file Fbx_Material.h
* @brief FBX用マテリアル構造体
* @author Ryunosuke Honda.
*/
#pragma once

#include "Base.h"
#include <d3d11.h>

/**
* FBX用マテリアル構造体
*/
struct Fbx_Material
{
	//!マテリアル名
	CHAR szName[100];
	//!アンビエント
	Vector4 Ka;
	//!ディフューズ
	Vector4 Kd;
	//!スペキュラー
	Vector4 Ks;
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
	Fbx_Material()
	{
		ZeroMemory(this, sizeof(Fbx_Material));
	}
	/**
	* @fn
	* デストラクタ
	*/
	~Fbx_Material()
	{
		SAFE_RELEASE(pTexture);
	}
};

/****** End of File *****************************************************/
