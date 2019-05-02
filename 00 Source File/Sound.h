/**
* @file Sound.h
* @brief 音リソースデータ構造体
* @author Ryunosuke Honda.
*/
#pragma once

#include "Base.h"
#include <xaudio2.h>
#include <mmsystem.h>

#pragma comment(lib,"winmm.lib")

/**
*	音リソースデータ構造体
*/
struct Sound
{
public:
	/**
	* @fn
	* デフォルトコンストラクタ
	*/
	Sound() {}

	/**
	* @fn
	* 仮想デストラクタ
	*/
	~Sound() {
		//	mpSourceVoice->DestroyVoice();
		SAFE_DELETE(mpWavBuffer);
		CoUninitialize();
	}

	/**
	* @fn
	* サウンド再生
	* @param (isLoop) ループ再生するか
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
			MessageBox(0, L"ソースボイスにサブミット失敗", 0, MB_OK);
			return;
		}
		mpSourceVoice->Start(0, XAUDIO2_COMMIT_NOW);
	}

	/**
	* @fn
	* サウンド停止
	*/
	void stop()
	{
		mpSourceVoice->Stop(0, XAUDIO2_COMMIT_NOW);
	}

	//!ソースボイス
	IXAudio2SourceVoice* mpSourceVoice;
	//!波形データ（フォーマット等を含まない、純粋に波形データのみ）
	BYTE* mpWavBuffer;
	//!波形データのサイズ
	DWORD mWavSize;
};

/* End of File *****************************************************/