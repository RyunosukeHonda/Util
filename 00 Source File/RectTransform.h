/**
* @file RectTransform.h
* @brief 2�����g�����X�t�H�[���N���X��`�t�@�C��
* @author Ryunosuke Honda.
*/
#pragma once

#include "Base.h"

/**
*	2�����g�����X�t�H�[���N���X
*	UI���W�n�Ŏg�p���܂�
*/
class RectTransform
{
public:
	/**
	 * @fn
	 * �f�t�H���g�R���X�g���N�^
	 */
	RectTransform();

	/**
	 * @fn
	 * �f�X�g���N�^
	 */
	virtual ~RectTransform();

	/**
	* @fn
	* �g�����X�t�H�[����񂩂烏�[���h�s����Z�o�A�i�[����֐�
	* @param (pOut) �i�[����s��̃|�C���^
	*/
	void makeWorld(Matrix4x4* pOut);

	//!�ʒu
	PROPERTY_READWRITE(Vector2, Position);
	//!��]
	PROPERTY_READWRITE(Vector3, EulerAngle);
	//!�X�P�[��
	PROPERTY_READWRITE(Vector2, Scale);
	//!�`��D��x�E�傫���قǎ�O�ɕ\������܂�
	PROPERTY_WRITEONLY(int, SortingLayer);
};

/* End of File *****************************************************/