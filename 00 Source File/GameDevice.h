/**
* @file GameDevice.h
* @brief �Q�[���f�o�C�X�N���X��`�t�@�C��
* @author Ryunosuke Honda.
*/
#pragma once

#include "IGameDevice.h"
#include "Renderer.h"
#include "SoundManager.h"
#include "InputManager.h"
#include "UtilMacro.h"

/**
*	�Q�[���f�o�C�X�N���X
*/
class GameDevice : public IGameDevice
{
	COPY_PROTECTED(GameDevice)

public:
	/**
	* @fn
	* �R���X�g���N�^
	* @param (wnd) �E�B���h�E���
	*/
	GameDevice(const HWND& wnd);

	// IGameDevice ����Čp������܂���
	virtual IRenderer & renderer() override;

	virtual IInput & input() override;

private:
	//!�����_���[
	Renderer mRenderer;
	//!����
	InputManager mInput;
};

/****** End of File *****************************************************/