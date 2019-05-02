/**
* @file Sound.h
* @brief �����\�[�X�f�[�^�\����
* @author Ryunosuke Honda.
*/
#pragma once

#include "Base.h"
#include <xaudio2.h>
#include <mmsystem.h>

#pragma comment(lib,"winmm.lib")

/**
*	�����\�[�X�f�[�^�\����
*/
struct Sound
{
public:
	/**
	* @fn
	* �f�t�H���g�R���X�g���N�^
	*/
	Sound() {}

	/**
	* @fn
	* ���z�f�X�g���N�^
	*/
	~Sound() {
		//	mpSourceVoice->DestroyVoice();
		SAFE_DELETE(mpWavBuffer);
		CoUninitialize();
	}

	/**
	* @fn
	* �T�E���h�Đ�
	* @param (isLoop) ���[�v�Đ����邩
	*/
	void play(bool isLoop)
	{
		XAUDIO2_BUFFER buffer = { 0 };
		buffer.pAudioData = mpWavBuffer;
		buffer.Flags = XAUDIO2_END_OF_STREAM;
		buffer.AudioBytes = mWavSize;
		if (isLoop)
		{
			buffer.LoopCount = XAUDIO2_LOOP_INFINITE;
		}
		if (FAILED(mpSourceVoice->SubmitSourceBuffer(&buffer)))
		{
			MessageBox(0, L"�\�[�X�{�C�X�ɃT�u�~�b�g���s", 0, MB_OK);
			return;
		}
		mpSourceVoice->Start(0, XAUDIO2_COMMIT_NOW);
	}

	/**
	* @fn
	* �T�E���h��~
	*/
	void stop()
	{
		mpSourceVoice->Stop(0, XAUDIO2_COMMIT_NOW);
	}

	//!�\�[�X�{�C�X
	IXAudio2SourceVoice* mpSourceVoice;
	//!�g�`�f�[�^�i�t�H�[�}�b�g�����܂܂Ȃ��A�����ɔg�`�f�[�^�̂݁j
	BYTE* mpWavBuffer;
	//!�g�`�f�[�^�̃T�C�Y
	DWORD mWavSize;
};

/* End of File *****************************************************/