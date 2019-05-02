/**
* @file Fbx_Material.h
* @brief FBX�p�}�e���A���\����
* @author Ryunosuke Honda.
*/
#pragma once

#include "Base.h"
#include <d3d11.h>

/**
* FBX�p�}�e���A���\����
*/
struct Fbx_Material
{
	//!�}�e���A����
	CHAR szName[100];
	//!�A���r�G���g
	Vector4 Ka;
	//!�f�B�t���[�Y
	Vector4 Kd;
	//!�X�y�L�����[
	Vector4 Ks;
	//!�e�N�X�`���[�t�@�C����
	CHAR szTextureName[100];
	//!�e�N�X�`���̃|�C���^
	ID3D11ShaderResourceView* pTexture;
	//!���̃}�e���A���ł���|���S����
	DWORD dwNumFace;

	/**
	* @fn
	* �R���X�g���N�^
	*/
	Fbx_Material()
	{
		ZeroMemory(this, sizeof(Fbx_Material));
	}
	/**
	* @fn
	* �f�X�g���N�^
	*/
	~Fbx_Material()
	{
		SAFE_RELEASE(pTexture);
	}
};

/****** End of File *****************************************************/
