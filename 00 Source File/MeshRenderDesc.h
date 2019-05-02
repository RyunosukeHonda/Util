/**
* @file MeshRenderDesc
* @brief ���b�V���`��L�q�q�e���v���[�g�E���f���̎�ނ��ƂɌp�����Ďg�p
* @author Ryunosuke Honda.
*/
#pragma once

#include "Transform.h"

/**
*	���b�V���`��L�q�q�e���v���[�g�E���f���̎�ނ��ƂɌp�����Ďg�p
*/
struct MeshRenderDesc
{
	/**
	* @fn
	* �R���X�g���N�^
	*/
	MeshRenderDesc() :
		mpTransform(nullptr),
		mAmbient(0, 0, 0, 0),
		mDiffuse(1, 0, 1, 1),
		mSpecular(0, 0, 0, 0) {}

	/**
	* @fn
	* ���z�f�X�g���N�^�E��Ɍp�����Ďg�p���邽��
	*/
	virtual ~MeshRenderDesc() {}

	//!�g�����X�t�H�[�����
	Transform* mpTransform;
	//!�A���r�G���g�F(��)�E�e�N�X�`���̐F�ɉ��Z����
	Color4 mAmbient;
	//!�f�B�t���[�Y�F(�g�U����)�E�e�N�X�`���̐F�ɉ��Z����
	Color4 mDiffuse;
	//!�X�y�L�����[�F(���ʔ���)�E�e�N�X�`���̐F�ɉ��Z����
	Color4 mSpecular;
};

/****** End of File *****************************************************/
