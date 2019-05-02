/**
* @file InputGamePad.cpp
* @brief �Q�[���p�b�h���͋@�\�N���X�����t�@�C��
* @author Ryunosuke Honda.
*/
#include "InputGamePad.h"

const float InputGamePad::STICK_MAX = 65535.0f / 2.0f;
const float InputGamePad::TRIGGER_MAX = 255.0f;

InputGamePad::InputGamePad() :
	mGamePadInfo(),
	mButtons(),
	mLeftSticks(),
	mRightSticks()
{
	//�R���g���[���[�ő吔�����[�v
	for (DWORD i = 0; i < MAX_CONTROLLERS; i++)
	{
		///�z��O�Q�Ƃ�h�����߂ɗ\�ߋ�f�[�^��o�^���Ă���
		mGamePadInfo.push_back(GamePadInfoMap());
		mButtons.push_back(0);
		mLeftSticks.push_back(Vector2());
		mRightSticks.push_back(Vector2());
	}
}

InputGamePad::~InputGamePad()
{
}

void InputGamePad::update()
{
	//�ڑ��m�F
	checkConnect();

	//�R���g���[���[�ő吔�����[�v
	for (DWORD i = 0; i < MAX_CONTROLLERS; i++)
	{
		//�ڑ�����Ă��Ȃ���Ώ������Ȃ�
		if (!GAME_PAD[i].bConnected) break;

		//�{�^�����͏��X�V
		mButtons[i] = GAME_PAD[i].state.Gamepad.wButtons;

		//�A�i���O���͏��X�V�E0~1�̊Ԃ̒l�ɂȂ�悤����
		//���x����������̂�0.1�����͂O�ɋ���
		mLeftSticks[i].x = abs(((float)GAME_PAD[i].state.Gamepad.sThumbLX / STICK_MAX)) < 0.2f ? 0.0f : (float)GAME_PAD[i].state.Gamepad.sThumbLX / STICK_MAX;
		mLeftSticks[i].y = abs(((float)GAME_PAD[i].state.Gamepad.sThumbLY / STICK_MAX)) < 0.2f ? 0.0f : (float)GAME_PAD[i].state.Gamepad.sThumbLY / STICK_MAX;;
		mRightSticks[i].x = abs(((float)GAME_PAD[i].state.Gamepad.sThumbRX / STICK_MAX)) < 0.2f ? 0.0 : (float)GAME_PAD[i].state.Gamepad.sThumbRX / STICK_MAX;;
		mRightSticks[i].y = abs(((float)GAME_PAD[i].state.Gamepad.sThumbRY / STICK_MAX)) < 0.2f ? 0.0 : (float)GAME_PAD[i].state.Gamepad.sThumbRY / STICK_MAX;;
	}
}

void InputGamePad::lateUpdate()
{
	//�o�^����Ă��遁�Q�[���Ŏg�p����L�[�̂ݏ���ۑ�
	for (DWORD i = 0; i < MAX_CONTROLLERS; i++)
	{
		for (auto pair : mGamePadInfo[i])
		{
			mGamePadInfo[i][pair.first] = mButtons[i] & pair.first;
		}
	}
}

bool InputGamePad::isButtonDown(const EPlayerIndex& index, const GamePadButton button)
{
	checkButtonInfoRegister(index, button);
	return mButtons[index] & button && !mGamePadInfo[index][button];
}

bool InputGamePad::isButtonPress(const EPlayerIndex& index, const GamePadButton button)
{
	checkButtonInfoRegister(index, button);
	return mButtons[index] & button && mGamePadInfo[index][button];
}

bool InputGamePad::isButtonUp(const EPlayerIndex& index, const GamePadButton button)
{
	checkButtonInfoRegister(index, button);
	return !(mButtons[index] & button) && mGamePadInfo[index][button];
}

bool InputGamePad::isButtonRelease(const EPlayerIndex& index, const GamePadButton button)
{
	checkButtonInfoRegister(index, button);
	return !(mButtons[index] & button) && !mGamePadInfo[index][button];
}

Vector2 & InputGamePad::getLeftStick(const EPlayerIndex & index)
{
	return mLeftSticks[index];
}

Vector2 & InputGamePad::getRightStick(const EPlayerIndex & index)
{
	return mRightSticks[index];
}

float InputGamePad::getLeftTrigger(const EPlayerIndex & index) const
{
	return (float)GAME_PAD[index].state.Gamepad.bLeftTrigger / TRIGGER_MAX;
}

float InputGamePad::getRightTrigger(const EPlayerIndex & index) const
{
	return (float)GAME_PAD[index].state.Gamepad.bRightTrigger / TRIGGER_MAX;
}

void InputGamePad::checkButtonInfoRegister(const EPlayerIndex& index, const GamePadButton button)
{
	//�L�[���͏��ۊǃ}�b�v�ɃL�[���o�^����Ă��Ȃ����
	if (mGamePadInfo[index].count(button) == 0)
	{
		//�L�[�͗�����Ă���
		mGamePadInfo[index][button] = false;
	}
}

void InputGamePad::checkConnect()
{
	DWORD dwResult;
	for (DWORD i = 0; i < MAX_CONTROLLERS; i++)
	{
		dwResult = XInputGetState(i, &GAME_PAD[i].state);

		if (dwResult == ERROR_SUCCESS)
			GAME_PAD[i].bConnected = true;
		else
			GAME_PAD[i].bConnected = false;
	}
}


/* End of File *****************************************************/