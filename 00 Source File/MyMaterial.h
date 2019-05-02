/**
* @file MyMaterial.h
* @brief �I���W�i���}�e���A���\����
* @author Ryunosuke Honda.
*/
#pragma once

#include "Base.h"
#include <d3d11.h>

/**
*	�I���W�i���}�e���A���\����
*/
struct MyMaterial
{
	//!�}�e���A����
	CHAR szName[100];
	//!�A���r�G���g
	Color4 Ka;
	//!�f�B�t���[�Y
	Color4 Kd;
	//!�X�y�L�����[
	Color4 Ks;
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
	MyMaterial()
	{
		ZeroMemory(this, sizeof(MyMaterial));
	}
	/**
	* @fn
	* �f�X�g���N�^
	*/
	~MyMaterial()
	{
		SAFE_RELEASE(pTexture);
	}
};

/****** End of File *****************************************************/
