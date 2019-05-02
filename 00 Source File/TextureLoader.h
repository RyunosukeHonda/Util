/**
* @file TextureLoader.h
* @brief �e�N�X�`��(�X�v���C�g�p�摜)�ǂݍ��݃N���X��`�t�@�C��
* @author Ryunosuke Honda.
*/
#pragma once

#include "Loader.h"

class IRenderer;

/**
*	�e�N�X�`���ǂݍ��݃N���X
*	�l�p�`�|���S���ɓ\��t����摜��ǂݍ���
*/
class TextureLoader : public Loader<LPCWSTR>
{
public:
	/**
	* @fn
	* �R���X�g���N�^
	* @param (renderer) �����_���[
	* @param (data) �t�@�C�����R���e�i
	*/
	TextureLoader(IRenderer& renderer, FileNameContainer<LPCWSTR>& data);

	// Loader ����Čp������܂���
	virtual void update() override;

private:
	//!�����_���[
	IRenderer& mRenderer;
};

/****** End of File *****************************************************/