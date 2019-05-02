/**
* @file ShaderTextureLoader.h
* @brief �V�F�[�_�[�e�N�X�`��(��`�ɓ\��t����)�ǂݍ��݃N���X��`�t�@�C��
* @author Ryunosuke Honda.
*/
#pragma once

#include "Loader.h"

class IRenderer;

/**
*	�V�F�[�_�[�e�N�X�`��(��`�ɓ\��t����)�ǂݍ��݃N���X
*/
class ShaderTextureLoader : public Loader<LPCWSTR>
{
public:
	/**
	* @fn
	* �R���X�g���N�^
	* @param (renderer) �����_���[
	* @param (data) �t�@�C�����R���e�i
	*/
	ShaderTextureLoader(IRenderer& renderer, FileNameContainer<LPCWSTR>& data);

	/**
	 * @fn
	 * �f�X�g���N�^
	 */
	~ShaderTextureLoader();

	// Loader ����Čp������܂���
	virtual void update() override;

private:
	//!�����_���[
	IRenderer& mRenderer;
};

/* End of File *****************************************************/