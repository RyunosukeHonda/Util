/**
* @file Entry.cpp
* @brief �G���g���[�|�C���g�쐬
* @author Ryunosuke Honda.
*/
///�x����\��
#pragma warning(disable : 4018)

#include <windows.h>
#include "Director.h"

///�f�o�b�O���̂݃R���\�[���\��
#ifdef _DEBUG
#include "DebugConsole.h"
#endif

///�K�v�ȃ��C�u�����t�@�C���̃��[�h
#pragma comment(lib,"winmm.lib")

#pragma comment(lib,"wininet.lib")

#pragma comment(lib,"d3dx10.lib")
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dx11.lib")
#pragma comment(lib,"d3dCompiler.lib")

//#pragma comment(lib,"libfbxsdk.lib")
//#pragma comment(lib,"libfbxsdk-md.lib")
#pragma comment(lib,"libfbxsdk-mt.lib")

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, INT)
{
#ifdef _DEBUG
	DebugConsole console;
#endif
	Director* pDirector = new Director;
	if (pDirector == NULL)
	{
		MessageBox(0, L"�N���X�������s�@�A�v�����I�����܂�", NULL, MB_OK);
		return 0;
	}
	//�i�s�̓f�B���N�^�[��
	pDirector->Run(hInstance);

	//�A�v���I��
	delete pDirector;

	return 0;
}

/****** End of File *****************************************************/