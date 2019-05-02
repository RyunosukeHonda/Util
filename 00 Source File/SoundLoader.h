/**
* @file SoundLoader.h
* @brief �����\�[�X�ǂݍ��݃N���X��`�t�@�C��
* @author Ryunosuke Honda.
*/
#pragma once

#include "Loader.h"

/**
*	�����\�[�X�ǂݍ��݃N���X
*/
class SoundLoader : public Loader<LPSTR>
{
public:
	/**
	* @fn
	* �R���X�g���N�^
	* @param (data) �f�[�^���R���e�i
	*/
	SoundLoader(FileNameContainer<LPSTR>& data);

	// Loader ����Čp������܂���
	virtual void update() override;
};

/****** End of File *****************************************************/