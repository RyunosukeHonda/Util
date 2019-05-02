/**
* @file SpriteRenderDesc
* @brief �X�v���C�g�`��L�q�q
* @author Ryunosuke Honda.
*/
#pragma once

#include "MeshRenderDesc.h"
#include "TextureID.h"

/**
*	�X�v���C�g�`��L�q�q
*/
struct SpriteRenderDesc : public MeshRenderDesc
{
	/**
	* @fn
	* �R���X�g���N�^
	*/
	SpriteRenderDesc(const TextureID& id) :
		MeshRenderDesc(),
		mID(id)
	{}

	//!�e�N�X�`��ID
	TextureID mID;
};

/****** End of File *****************************************************/
