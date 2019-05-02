/**
* @file InputMouse.cpp
* @brief �}�E�X���̓N���X�����t�@�C��
* @author Ryunosuke Honda.
*/
#include "InputMouse.h"
#include "Screen.h"

InputMouse::InputMouse(LPDIRECTINPUT8 pDinput, const HWND& hwnd) :
	mMouseInfo(),
	dims()
{
	// �uDirectInput�f�o�C�X�v�I�u�W�F�N�g�̍쐬
	pDinput->CreateDevice(GUID_SysMouse, &mpMouseDevice, NULL);
	// �f�o�C�X���}�E�X�ɐݒ�
	mpMouseDevice->SetDataFormat(&c_dfDIMouse2);
	// �������x���̐ݒ�
	mpMouseDevice->SetCooperativeLevel(hwnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	// �f�o�C�X���u�擾�v����
	mpMouseDevice->Acquire();

	//�}�E�X���}�b�v�ɗ\�ߏ�������o�^
	mMouseInfo[EMouseButton::LEFT] = false;
	mMouseInfo[EMouseButton::RIGHT] = false;
	mMouseInfo[EMouseButton::CENTER] = false;
}

InputMouse::~InputMouse()
{
}

void InputMouse::update()
{
	//�}�E�X���͏��̍X�V
	if (FAILED(mpMouseDevice->GetDeviceState(sizeof(DIMOUSESTATE2), &dims)))
	{
		mpMouseDevice->Acquire();
		return;
	}

	mPos.x += dims.lX;
	mPos.y += dims.lY;

	if (mPos.x < 0)
	{
		mPos.x = 0;
	}
	else if (mPos.x > Screen::WINDOW_WIDTH)
	{
		mPos.x = Screen::WINDOW_WIDTH;
	}
	if (mPos.y < 0)
	{
		mPos.y = 0;
	}
	else if (mPos.y > Screen::WINDOW_HEIGHT)
	{
		mPos.y = Screen::WINDOW_HEIGHT;
	}

}

void InputMouse::lateUpdate()
{
	//�}�E�X�̊e�����i�[
	//���{�^��
	mMouseInfo[EMouseButton::LEFT] = dims.rgbButtons[EMouseButton::LEFT] & 0x80;
	//�E�{�^��
	mMouseInfo[EMouseButton::RIGHT] = dims.rgbButtons[EMouseButton::RIGHT] & 0x80;
	//���{�^��
	mMouseInfo[EMouseButton::CENTER] = dims.rgbButtons[EMouseButton::CENTER] & 0x80;
}

bool InputMouse::isMouseButtonDown(EMouseButton mouse)
{
	//���t���[��������Ă��āA�O�t���[���ŉ�����Ă��Ȃ����true
	return dims.rgbButtons[mouse] & 0x80 && !mMouseInfo[mouse];
}

bool InputMouse::isMouseButtonPress(EMouseButton mouse)
{
	//���t���[��������Ă��āA�O�t���[���ł�������Ă����true
	return dims.rgbButtons[mouse] & 0x80 && mMouseInfo[mouse];
}

bool InputMouse::isMouseButtonUp(EMouseButton mouse)
{
	//���t���[��������Ă��Ȃ����A�O�t���[���ŉ�����Ă����true
	return dims.rgbButtons[mouse] == 0x00 && mMouseInfo[mouse];
}

bool InputMouse::isMouseButtonRelease(EMouseButton mouse)
{
	//���t���[��������Ă��Ȃ����A�O�t���[���ł�������Ă��Ȃ����true
	return dims.rgbButtons[mouse] == 0x00 && !mMouseInfo[mouse];
}

/* End of File *****************************************************/