/**
* @file FBXSkinMeshLoader.h
* @brief FBX�X�L�����b�V���ǂݍ��݃N���X��`�t�@�C��
* @author Ryunosuke Honda.
*/
#pragma once

#include "Loader.h"

class IRenderer;

/**
*	FBX�X�L�����b�V���ǂݍ��݃N���X
*/
class FBXSkinMeshLoader : public Loader<LPSTR>
{
public:
	/**
	* @fn
	* �R���X�g���N�^
	* @param (renderer) �����_���[
	* @param (data) �t�@�C�����R���e�i
	*/
	FBXSkinMeshLoader(IRenderer& renderer, FileNameContainer<LPSTR>& data);
	
	/**
	 * @fn
	 * �f�X�g���N�^
	 */
	~FBXSkinMeshLoader();

	// Loader ����Čp������܂���
	virtual void update() override;

private:
	//!�����_���[
	IRenderer& mRenderer;
};

/* End of File *****************************************************/