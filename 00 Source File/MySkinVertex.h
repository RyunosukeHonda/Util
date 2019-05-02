/**
* @file MySkinVertex.h
* @brief �X�L�����b�V���p���_�\����
* @author Ryunosuke Honda.
*/
#pragma once

#include "Base.h"

/**
*	�X�L�����b�V���p ���_�\����
*/
struct MySkinVertex
{
	/**
	* @fn
	* �R���X�g���N�^
	*/
	MySkinVertex()
	{
		ZeroMemory(this, sizeof(MySkinVertex));
	}

	//!���_�ʒu
	Vector3 vPos;
	//!���_�@��
	Vector3 vNorm;
	//!UV���W
	Vector2 vTex;
	//!�{�[���@�ԍ�
	UINT bBoneIndex[4];
	//!�{�[���@�d��
	float bBoneWeight[4];
};

/****** End of File *****************************************************/
