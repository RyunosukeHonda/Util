/**
* @file InputKey.cpp
* @brief �L�[���̓N���X�����t�@�C��
* @author Ryunosuke Honda.
*/
#include "InputKey.h"

InputKey::InputKey(LPDIRECTINPUT8 pDinput, const HWND& hwnd) :
	mKeyInfo()
{
	// �uDirectInput�f�o�C�X�v�I�u�W�F�N�g�̍쐬
	pDinput->CreateDevice(GUID_SysKeyboard, &mpKeyDevice, NULL);

	// �f�o�C�X���L�[�{�[�h�ɐݒ�
	mpKeyDevice->SetDataFormat(&c_dfDIKeyboard);

	// �������x���̐ݒ�
	mpKeyDevice->SetCooperativeLevel(hwnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);

	// �f�o�C�X���u�擾�v����
	mpKeyDevice->Acquire();
}

InputKey::~InputKey()
{
	SAFE_RELEASE(mpKeyDevice);
}

void InputKey::update()
{
	//�L�[���͏��̍X�V
	HRESULT hr = mpKeyDevice->Acquire();
	if ((hr == DI_OK) || (hr == S_FALSE))
	{
		mpKeyDevice->GetDeviceState(sizeof(diks), &diks);
	}
}

void InputKey::lateUpdate()
{
	//�o�^����Ă��遁�Q�[���Ŏg�p����L�[�̂ݏ���ۑ�
	for (auto pair : mKeyInfo) {
		mKeyInfo[pair.first] = diks[pair.first] & 0x80;
	}
}

bool InputKey::isKeyDown(KeyCode key)
{
	checkKeyInfoRegister(key);
	return diks[key] & 0x80 && !mKeyInfo[key];
}

bool InputKey::isKeyPress(KeyCode key)
{
	checkKeyInfoRegister(key);
	return diks[key] & 0x80 && mKeyInfo[key];
}

bool InputKey::isKeyUp(KeyCode key)
{
	checkKeyInfoRegister(key);
	return !(diks[key] & 0x80) && mKeyInfo[key];
}

bool InputKey::isKeyRelease(KeyCode key)
{
	checkKeyInfoRegister(key);
	return !(diks[key] & 0x80) && !mKeyInfo[key];
}

void InputKey::checkKeyInfoRegister(KeyCode key)
{
	//�L�[���͏��ۊǃ}�b�v�ɃL�[���o�^����Ă��Ȃ����
	if (mKeyInfo.count(key) == 0)
	{
		//�L�[�͗�����Ă���
		mKeyInfo[key] = false;
	}
}

/* End of File *****************************************************/