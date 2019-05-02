/**
* @file MySkinMaterial.h
* @brief �X�L�����b�V���p�}�e���A���\����
* @author Ryunosuke Honda.
*/
#pragma once

#include "Base.h"

/**
*	�X�L�����b�V���p�}�e���A���\����
*/
struct MySkinMaterial
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
	MySkinMaterial()
	{
		ZeroMemory(this, sizeof(MySkinMaterial));
	}
	/**
	* @fn
	* �R���X�g���N�^
	*/
	~MySkinMaterial()
	{
		SAFE_RELEASE(pTexture);
	}
};

/****** End of File *****************************************************/
