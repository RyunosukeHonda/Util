/**
* @file OBJStaticMeshRenderDesc.h
* @brief OBJ���b�V���`��L�q�q
* @author Ryunosuke Honda.
*/
#pragma once

#include "MeshRenderDesc.h"
#include "OBJStaticMeshID.h"

/**
*	OBJ���b�V���`��L�q�q
*/
struct OBJStaticMeshRenderDesc : public MeshRenderDesc
{
	/**
	*	@fn
	*	�R���X�g���N�^
	*/
	OBJStaticMeshRenderDesc(const OBJMeshID& id) :
		MeshRenderDesc(),
		mID(id)
	{}

	//!���f��ID
	OBJMeshID mID;
};

/****** End of File *****************************************************/
