/**
* @file IInputManager.h
* @brief ���͋@�\�Ǘ��N���X��`�t�@�C��
* @author Ryunosuke Honda.
*/
#pragma once

#include "IInput.h"
#include "InputKey.h"
#include "InputMouse.h"
#include "InputGamePad.h"
#include <dinput.h>

#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"dinput8.lib")

/**
*	���͋@�\�N���X
*/
class InputManager : public IInput
{
public:
	/**
	 * @fn
	 * �f�t�H���g�R���X�g���N�^
	 * @brief �����Ɠ����Ɋe�@�\�̏��������s���܂�
	 */
	InputManager(const HWND& hwnd);
	
	/**
	 * @fn
	 * �f�X�g���N�^
	 */
	~InputManager();

	// IInput ����Čp������܂���
	virtual void update() override;
	virtual void lateUpdate() override;
	virtual bool isKeyDown(KeyCode key) override;
	virtual bool isKeyPress(KeyCode key) override;
	virtual bool isKeyUp(KeyCode key) override;
	virtual bool isKeyRelease(KeyCode key) override;
	virtual bool isMouseButtonDown(EMouseButton mouse) override;
	virtual bool isMouseButtonPress(EMouseButton mouse) override;
	virtual bool isMouseButtonUp(EMouseButton mouse) override;
	virtual bool isMouseButtonRelease(EMouseButton mouse) override;
	virtual const Vector2 & getMousePosition() override;
	virtual bool isButtonDown(const EPlayerIndex& index, const GamePadButton button) override;
	virtual bool isButtonPress(const EPlayerIndex& index, const GamePadButton button) override;
	virtual bool isButtonUp(const EPlayerIndex& index, const GamePadButton button) override;
	virtual bool isButtonRelease(const EPlayerIndex& index, const GamePadButton button) override;
	virtual Vector2 & getLeftStick(const EPlayerIndex & index) override;
	virtual Vector2 & getRightStick(const EPlayerIndex & index) override;
	virtual float getLeftTrigger(const EPlayerIndex & index) override;
	virtual float getRightTrigger(const EPlayerIndex & index) override;

private:
	//!���͋@��
	LPDIRECTINPUT8 mpDinput;
	//!�L�[�{�[�h���̓N���X
	InputKey* mpKey;
	//!�}�E�X���̓N���X
	InputMouse* mpMouse;
	//!�Q�[���p�b�h���̓N���X
	InputGamePad* mpGamePad;
};

/* End of File *****************************************************/