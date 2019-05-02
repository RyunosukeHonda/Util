/**
* @file FBXHierarchyMeshRenderDesc
* @brief FBX�K�w���b�V���`��L�q�q
* @author Ryunosuke Honda.
*/
#pragma once

#include "MeshRenderDesc.h"
#include "FBXHierarchyMeshID.h"

/**
*	FBX�K�w���b�V���`��L�q�q
*/
struct FBXHierarchyMeshRenderDesc : public MeshRenderDesc
{
	/**
	*	@fn
	*	�R���X�g���N�^
	*/
	FBXHierarchyMeshRenderDesc(const FBXHierarchyID& id) :
		MeshRenderDesc(),
		mID(id),
		mFrame(0)
	{
	}

	//!���f��ID
	FBXHierarchyID mID;
	//!�A�j���[�V�����t���[��
	int mFrame;
};

/****** End of File *****************************************************/
