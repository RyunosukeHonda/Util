/**
* @file PolyTable.h
* @brief �P���_�̋��L�@�ő�20�|���S���܂�
* @author Ryunosuke Honda.
*/
#pragma once

#include "Base.h"

/**
*	�P���_�̋��L�@�ő�20�|���S���܂�
*/
struct PolyTable
{
	/**
	* @fn
	* �R���X�g���N�^
	*/
	PolyTable()
	{
		ZeroMemory(this, sizeof(PolyTable));
	}

	//!�|���S���ԍ�
	int PolyIndex[20]; 
	//!3�̒��_�̂����A���Ԗڂ�
	int Index123[20];
	//!�����Ă���|���S����
	int NumRef;
};

/****** End of File *****************************************************/
