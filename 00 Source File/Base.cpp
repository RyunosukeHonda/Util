/**
* @file Base.cpp
* @brief Base.h�Ŏ�������K�v������v�f�̎����t�@�C��
* @author Ryunosuke Honda.
*/
#include "Base.h"
WCHAR g_szRootPath[1024]={0};

void InitDirectory(WCHAR* root)
{
	wcsncpy(g_szRootPath,root,wcslen(root));
}

void SetRootDirectory()
{
	SetCurrentDirectory(g_szRootPath);
}

void SetSoundDirectory()
{
	WCHAR tmp[1100]={0};
	wcsncpy(tmp,g_szRootPath,wcslen(g_szRootPath));
	wcscat(tmp,L"\\04 Sound File");
	SetCurrentDirectory(tmp);
}

void SetDataDirectory()
{
	WCHAR tmp[1100]={0};
	wcsncpy(tmp,g_szRootPath,wcslen(g_szRootPath));
	wcscat(tmp,L"\\01 Data File");
	SetCurrentDirectory(tmp);
}

void SetVisualDirectory()
{
	WCHAR tmp[1100]={0};
	wcsncpy(tmp,g_szRootPath,wcslen(g_szRootPath));
	wcscat(tmp,L"\\02 Visual File");
	SetCurrentDirectory(tmp);
}

void SetShaderDirectory()
{
	WCHAR tmp[1100]={0};
	wcsncpy(tmp,g_szRootPath,wcslen(g_szRootPath));
	wcscat(tmp,L"\\03 Shader File");
	SetCurrentDirectory(tmp);
}

/****** End of File *****************************************************/
