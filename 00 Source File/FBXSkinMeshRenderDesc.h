/**
* @file FBXSkinMeshRenderDesc.h
* @brief FBX�X�L�����b�V���`��L�q�q
* @author Ryunosuke Honda.
*/
#pragma once

#include "MeshRenderDesc.h"
#include "FBXSkinMeshID.h"

/**
*	FBX�X�L�����b�V���`��L�q�q
*/
struct FBXSkinMeshRenderDesc : public MeshRenderDesc
{
	/**
	*	@fn
	*	�R���X�g���N�^
	*/
	FBXSkinMeshRenderDesc(const FBXSkinID& id) :
		MeshRenderDesc(),
		mID(id),
		mFrame(0) {}

	//!���f��ID
	FBXSkinID mID;
	//!�A�j���[�V�����t���[��
	int mFrame;
};

/****** End of File *****************************************************/
