/**
* @file DebugConsole.h
* @brief �f�o�b�O�p�̃R���\�[���E�B���h�E�N���X��`�t�@�C��
* @author Ryunosuke Honda.
*/

#pragma once

#include <wincon.h>
#include <stdlib.h>
#include <iostream>

/**
*	�f�o�b�O�p�R���\�[���N���X
*/
class DebugConsole
{
public:
	/**
	* @fn
	* �R���X�g���N�^
	* @brief �K�v�ȏ����������ɍs��
	*/
	DebugConsole() {
		::AllocConsole();
		freopen_s(&fp, "CON", "w", stdout);    // �W���o�͂̊��蓖��
		cout << "DebugConsole awaking..." << endl;
	}

	/**
	* @fn
	* �f�X�g���N�^
	* @brief ����������s��
	*/
	~DebugConsole() {
		cout << "DebugConsole closing..." << endl;
		fclose(fp);
		::FreeConsole();
	}

private:
	//!�t�@�C���|�C���^
	FILE *fp;
};

/****** End of File *****************************************************/
