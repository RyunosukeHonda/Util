/**
* @file SoundManager.cpp
* @brief �����\�[�X�Ǘ��N���X�����t�@�C��
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
		Debug::messageBox(L"XAudioCreate ���s");
		return;
	}
	if (FAILED(mpXAudio2->CreateMasteringVoice(&mpMasteringVoice)))
	{
		CoUninitialize();
		Debug::messageBox(L"Create MasteringVoice ���s");
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
	HMMIO hMmio = NULL;//Windows�}���`���f�B�AAPI�̃n���h��(Windows�}���`���f�B�AAPI��WAV�t�@�C���֌W�̑���p��API)
	DWORD dwWavSize = 0;//WAV�t�@�C�����@WAV�f�[�^�̃T�C�Y�iWAV�t�@�C����WAV�f�[�^�Ő�߂��Ă���̂ŁA�قڃt�@�C���T�C�Y�Ɠ���j
	WAVEFORMATEX* pwfex;//WAV�̃t�H�[�}�b�g ��j16�r�b�g�A44100Hz�A�X�e���I�Ȃ�
	MMCKINFO ckInfo;//�@�`�����N���
	MMCKINFO riffckInfo;// �ŏ㕔�`�����N�iRIFF�`�����N�j�ۑ��p
	PCMWAVEFORMAT pcmWaveForm;
	//WAV�t�@�C�����̃w�b�_�[���i���f�[�^�ȊO�j�̊m�F�Ɠǂݍ���
	hMmio = mmioOpenA(fileName, NULL, MMIO_ALLOCBUF | MMIO_READ);
	//�t�@�C���|�C���^��RIFF�`�����N�̐擪�ɃZ�b�g����
	mmioDescend(hMmio, &riffckInfo, NULL, 0);
	// �t�@�C���|�C���^��'f' 'm' 't' ' ' �`�����N�ɃZ�b�g����
	ckInfo.ckid = mmioFOURCC('f', 'm', 't', ' ');
	mmioDescend(hMmio, &ckInfo, &riffckInfo, MMIO_FINDCHUNK);
	//�t�H�[�}�b�g��ǂݍ���
	mmioRead(hMmio, (HPSTR)&pcmWaveForm, sizeof(pcmWaveForm));
	pwfex = (WAVEFORMATEX*)new CHAR[sizeof(WAVEFORMATEX)];
	memcpy(pwfex, &pcmWaveForm, sizeof(pcmWaveForm));
	pwfex->cbSize = 0;
	mmioAscend(hMmio, &ckInfo, 0);
	// WAV�t�@�C�����̉��f�[�^�̓ǂݍ���	
	ckInfo.ckid = mmioFOURCC('d', 'a', 't', 'a');
	mmioDescend(hMmio, &ckInfo, &riffckInfo, MMIO_FINDCHUNK);//�f�[�^�`�����N�ɃZ�b�g
	dwWavSize = ckInfo.cksize;
	sound->mpWavBuffer = new BYTE[dwWavSize];
	//mpWavBuffer[iIndex] = new BYTE[dwWavSize];
	DWORD dwOffset = ckInfo.dwDataOffset;
	mmioRead(hMmio, (HPSTR)sound->mpWavBuffer, dwWavSize);
	//�\�[�X�{�C�X�Ƀf�[�^���l�ߍ���	
	if (FAILED(mpXAudio2->CreateSourceVoice(&sound->mpSourceVoice, pwfex)))
	{
		MessageBox(0, L"�\�[�X�{�C�X�쐬���s", 0, MB_OK);
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