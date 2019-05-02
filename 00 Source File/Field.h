/**
* @file Field.h
* @brief �X�e�[�W���f���N���X��`�t�@�C��
* @author Ryunosuke Honda.
*/
#pragma once

#include "PlaneCollider.h"
#include "IObject.h"
#include "OBJStaticMeshRenderDesc.h"

/**
*	�X�e�[�W���f���N���X
*/
class Field : public PlaneCollider, public IObject
{
public:
	/**
	 * @fn
	 * �f�t�H���g�R���X�g���N�^
	 */
	Field();

	/**
	 * @fn
	 * �f�X�g���N�^
	 */
	~Field();

	/**
	* @fn
	* �X�e�[�W�`��
	* @param (renderer) �`��N���X
	*/
	virtual void draw(IRenderer& renderer) override;

private:
	using base = PlaneCollider;
	//!���f���`��L�q�q
	OBJStaticMeshRenderDesc mDesc;
};

/* End of File *****************************************************/