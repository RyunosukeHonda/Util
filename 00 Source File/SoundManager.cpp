/**
* @file SoundManager.cpp
* @brief 音リソース管理クラス実装ファイル
* @author Ryunosuke Honda.
*/
#include "SoundManager.h"

SoundManager::SoundManager()
{
	init();
}

SoundManager::~SoundManager()
{
	SAFE_RELEASE(mpXAudio2);
}

void SoundManager::init()
{
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	if (FAILED(XAudio2Create(&mpXAudio2, 0)))
	{
		CoUninitialize();
		Debug::messageBox(L"XAudioCreate 失敗");
		return;
	}
	if (FAILED(mpXAudio2->CreateMasteringVoice(&mpMasteringVoice)))
	{
		CoUninitialize();
		Debug::messageBox(L"Create MasteringVoice 失敗");
		return;
	}
}

void SoundManager::remove(const SoundID& id)
{
}

void SoundManager::clear()
{
}

void SoundManager::load(const SoundID& id, char* fileName)
{
	SetSoundDirectory();
	Sound* sound = new Sound();
	HMMIO hMmio = NULL;//WindowsマルチメディアAPIのハンドル(WindowsマルチメディアAPIはWAVファイル関係の操作用のAPI)
	DWORD dwWavSize = 0;//WAVファイル内　WAVデータのサイズ（WAVファイルはWAVデータで占められているので、ほぼファイルサイズと同一）
	WAVEFORMATEX* pwfex;//WAVのフォーマット 例）16ビット、44100Hz、ステレオなど
	MMCKINFO ckInfo;//　チャンク情報
	MMCKINFO riffckInfo;// 最上部チャンク（RIFFチャンク）保存用
	PCMWAVEFORMAT pcmWaveForm;
	//WAVファイル内のヘッダー情報（音データ以外）の確認と読み込み
	hMmio = mmioOpenA(fileName, NULL, MMIO_ALLOCBUF | MMIO_READ);
	//ファイルポインタをRIFFチャンクの先頭にセットする
	mmioDescend(hMmio, &riffckInfo, NULL, 0);
	// ファイルポインタを'f' 'm' 't' ' ' チャンクにセットする
	ckInfo.ckid = mmioFOURCC('f', 'm', 't', ' ');
	mmioDescend(hMmio, &ckInfo, &riffckInfo, MMIO_FINDCHUNK);
	//フォーマットを読み込む
	mmioRead(hMmio, (HPSTR)&pcmWaveForm, sizeof(pcmWaveForm));
	pwfex = (WAVEFORMATEX*)new CHAR[sizeof(WAVEFORMATEX)];
	memcpy(pwfex, &pcmWaveForm, sizeof(pcmWaveForm));
	pwfex->cbSize = 0;
	mmioAscend(hMmio, &ckInfo, 0);
	// WAVファイル内の音データの読み込み	
	ckInfo.ckid = mmioFOURCC('d', 'a', 't', 'a');
	mmioDescend(hMmio, &ckInfo, &riffckInfo, MMIO_FINDCHUNK);//データチャンクにセット
	dwWavSize = ckInfo.cksize;
	sound->mpWavBuffer = new BYTE[dwWavSize];
	//mpWavBuffer[iIndex] = new BYTE[dwWavSize];
	DWORD dwOffset = ckInfo.dwDataOffset;
	mmioRead(hMmio, (HPSTR)sound->mpWavBuffer, dwWavSize);
	//ソースボイスにデータを詰め込む	
	if (FAILED(mpXAudio2->CreateSourceVoice(&sound->mpSourceVoice, pwfex)))
	{
		MessageBox(0, L"ソースボイス作成失敗", 0, MB_OK);
		return;
	}
	sound->mWavSize = dwWavSize;
	add(id, sound);
}

void SoundManager::play(const SoundID& id, bool isLoop)
{
	get(id)->play(isLoop);
}

void SoundManager::stop(const SoundID& id)
{
	get(id)->stop();
}

/* End of File *****************************************************/