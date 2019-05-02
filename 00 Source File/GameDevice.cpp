/**
* @file GameDevice.cpp
* @brief �Q�[���S�̂Ŏg�p����f�o�C�X�N���X�̊Ǘ��N���X�����t�@�C��
* @author Ryunosuke Honda.
*/

#include "GameDevice.h"

GameDevice::GameDevice(const HWND & wnd) :
	mRenderer(wnd),
	mInput(wnd)
{

}

IRenderer & GameDevice::renderer()
{
	return mRenderer;
}

IInput & GameDevice::input()
{
	return mInput;
}

/****** End of File *****************************************************/