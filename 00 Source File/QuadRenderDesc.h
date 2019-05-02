/**
* @file QuadRendererDesc
* @brief �V�F�[�_�[�e�N�X�`���`��p��`���L�q�q
* @author Ryunosuke Honda.
*/
#pragma once

#include "MeshRenderDesc.h"
#include "ShaderTextureID.h"

/**
*	�V�F�[�_�[�e�N�X�`���`��p��`���L�q�q
*/
struct QuadRenderDesc : MeshRenderDesc
{
	/**
	* @fn
	* �R���X�g���N�^
	*/
	QuadRenderDesc(const ShaderTextureID& id) :
		MeshRenderDesc(),
		mID(id),
		mTime(0.0f)
	{}

	/**
	* @fn
	* �f�X�g���N�^
	*/
	~QuadRenderDesc() {}

	//!�V�F�[�_�[�e�N�X�`��ID
	ShaderTextureID mID;
	//!�A�j���[�V��������
	float mTime;
};

/****** End of File *****************************************************/
