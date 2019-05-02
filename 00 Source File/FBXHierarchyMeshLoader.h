/**
* @file FBXHierarchyMeshLoader.h
* @brief FBX�K�w���b�V���ǂݍ��݃N���X��`�t�@�C��
* @author Ryunosuke Honda.
*/
#pragma once

#include "Loader.h"

class IRenderer;

/**
*	FBX�K�w���b�V���ǂݍ��݃N���X
*/
class FBXHierarchyMeshLoader : public Loader<LPSTR>
{
public:
	/**
	* @fn
	* �R���X�g���N�^
	* @param (renderer) �����_���[
	* @param (data) �t�@�C�����R���e�i
	*/
	FBXHierarchyMeshLoader(IRenderer& renderer, FileNameContainer<CHAR*>& data);

	/**
	* @fn
	* �f�X�g���N�^
	*/
	~FBXHierarchyMeshLoader();

	// Loader ����Čp������܂���
	virtual void update() override;

private:
	//!�����_���[
	IRenderer& mRenderer;
};

/* End of File *****************************************************/