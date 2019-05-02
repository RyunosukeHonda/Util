/**
* @file OBJStaticMeshLoader.h
* @brief OBJ�`���X�^�e�B�b�N���b�V���ǂݍ��݃N���X��`�t�@�C��
* @author Ryunosuke Honda.
*/
#pragma once

#include "Loader.h"

class IRenderer;

/**
*	OBJ�`���X�^�e�B�b�N���b�V���ǂݍ��݃N���X
*/
class OBJStaticMeshLoader : public Loader<LPSTR>
{
public:
	/**
	* @fn
	* �R���X�g���N�^
	* @param (renderer) �����_���[
	* @param (data) �t�@�C�����R���e�i
	*/
	OBJStaticMeshLoader(IRenderer& renderer, FileNameContainer<LPSTR>& data);

	// Loader ����Čp������܂���
	virtual void update() override;

private:
	//!�����_���[
	IRenderer& mRenderer;
};

/* End of File *****************************************************/