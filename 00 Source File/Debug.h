/**
* @file Debug.h
* @brief �f�o�b�O���̂ݎg�p����ėp�֐��܂Ƃ߃N���X
* @author Ryunosuke Honda.
*/
#pragma once

#include <iostream>
#include <string>

using namespace std;

#if _DEBUG
/**
* @def PRINT
* �����̒��g���ȒP�ɏo�͂���}�N��
* @param (var) ���g��m�肽���ϐ�
*/
#define PRINT(var) std::cout<<#var"= "<<var<<std::endl

/**
*	�f�o�b�O���̂ݎg�p����ėp�֐��܂Ƃ߃N���X
*/
class Debug
{
public:
	static void log(const char* mes)
	{
		cout << mes << endl;
	}

	static void log(string& mes)
	{
		cout << mes << endl;
	}

	static void messageBox(LPCWSTR mes)
	{
		MessageBox(0, mes, NULL, MB_OK);
	}
};

#else

#define PRINT(var) 
/**
*	�����[�X���͂�����
*	���������̂Ȃ������֐��𗅗񂵂Ă������Ƃ�
*	�f�o�b�O�G���[��h�~����
*/
class Debug
{
public:
	///FIXME �����[�X�p�֐�
	static void log(const char* mes) {}
	static void log(string& mes) {}
	static void messageBox(LPCWSTR mes) {}
};


#endif

/* End of File *****************************************************/