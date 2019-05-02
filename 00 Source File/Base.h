/**
* @file Base.h
* @brief �O���[�o���Ɏg�p����w�b�_�[�A���C�u�����A�}�N���Ȃǂ��܂Ƃ߂Ă����t�@�C��
* @author Ryunosuke Honda.
*/
#pragma once
#pragma warning(disable : 4005)

///�C���N���[�h�t�@�C��
#include <string>
#include <stdio.h>

#include "PropertyMacro.h"
#include "MathUtility.h"
#include "Debug.h"
#include "GameDef.h"

///�}�N��
#define SAFE_DELETE(p) { if(p) { delete (p); (p)=NULL; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p); (p)=NULL; } }
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }
#define MFAIL(code,string) if(FAILED( code ) ) { MessageBox(0,string,L"error",MB_OK); return E_FAIL; }
#define MFALSE(code,string) if(!( code ) ) { MessageBox(0,string,L"error",MB_OK); return E_FAIL; }
#define MSG(t) MessageBox(0,t,0,MB_OK);
#define SIZE_OF_ARRAY(array)  (sizeof(array)/sizeof((array)[0]))
#define CLAMP(x, low, high) (x > high)? high : (x < low)? low : x

using namespace std;

/**
*	�S�N���X�Ɍp�������Ă������ƂŕK�v�ɉ����đS�N���X�ɕϐ����ǉ��ł���悤�ɂ���
*/
class CElement
{
};

//
//�֐��v���g�^�C�v
//

/**
* @fn
* �f�B���N�g��������
* @brief
* ���\�[�X�ǂݍ��݂��Ȍ��ɂ��邽�߂̊֐��Ɏg�p����
* ���[�g�f�B���N�g���̐ݒ���s��
* @param (root) ���[�g�f�B���N�g��
*/
void InitDirectory(WCHAR* root);

/**
* @fn
* ���[�g�f�B���N�g���ɐݒ�
*/
void SetRootDirectory();

/**
* @fn
* �f�[�^�f�B���N�g���ɐݒ�
*/
void SetDataDirectory();

/**
* @fn
* �r�W���A��(���f���A�e�N�X�`���Ȃ�)�f�B���N�g���ݒ�
*/
void SetVisualDirectory();

/**
* @fn
* �V�F�[�_�[�f�B���N�g���ɐݒ�
*/
void SetShaderDirectory();

/**
* @fn
* �T�E���h�f�B���N�g���ɐݒ�
*/
void SetSoundDirectory();

/****** End of File *****************************************************/