/**
* @file IInput.h
* @brief ���͋@��C���^�[�t�F�[�X
* @author Ryunosuke Honda.
*/
#pragma once

#include "Base.h"
#include <XInput.h>
#include "EMouseButton.h"
#include "EPlayerIndex.h"

using KeyCode = int;
using GamePadButton = unsigned short;

/**
*	���͋@��C���^�[�t�F�[�X
*/
class IInput
{
public:
	/**
	* @fn
	* �X�V����
	* @brief ���͂��擾����
	*/
	virtual void update() = 0;

	/**
	* @fn
	* �x���X�V����
	* @brief �擾�������͏������t���[���Ŏg�p���邽�߂ɕۑ�����
	*/
	virtual void lateUpdate() = 0;


	/**
	* @fn
	* �L�[�������ꂽ�u�Ԃ��擾
	* @param (key) �L�[�R�[�h�A��`�ς݂�16�i��[DIK_]�Ŏw��
	*/
	virtual bool isKeyDown(KeyCode key) = 0;

	/**
	* @fn
	* �L�[��������Ă��邩���擾
	* @param (key) �L�[�R�[�h�A��`�ς݂�16�i��[DIK_]�Ŏw��
	*/
	virtual bool isKeyPress(KeyCode key) = 0;

	/**
	* @fn
	* �L�[�������ꂽ�u�Ԃ��擾
	* @param (key) �L�[�R�[�h�A��`�ς݂�16�i��[DIK_]�Ŏw��
	*/
	virtual bool isKeyUp(KeyCode key) = 0;

	/**
	* @fn
	* �L�[��������Ă��邩
	* @param (key) �L�[�R�[�h�A��`�ς݂�16�i��[DIK_]�Ŏw��
	*/
	virtual bool isKeyRelease(KeyCode key) = 0;

	/**
	* @fn
	* �}�E�X�{�^���������ꂽ�u�Ԃ��擾
	* @param (mouse) �}�E�X�{�^���A��`�ς݂̗񋓌^�Ŏw��
	*/
	virtual bool isMouseButtonDown(EMouseButton mouse) = 0;

	/**
	* @fn
	* �}�E�X�{�^����������Ă��邩���擾
	* @param (mouse) �}�E�X�{�^���A��`�ς݂̗񋓌^�Ŏw��
	*/
	virtual bool isMouseButtonPress(EMouseButton mouse) = 0;

	/**
	* @fn
	* �}�E�X�{�^���������ꂽ�u�Ԃ��擾
	* @param (mouse) �}�E�X�{�^���A��`�ς݂̗񋓌^�Ŏw��
	*/
	virtual bool isMouseButtonUp(EMouseButton mouse) = 0;

	/**
	* @fn
	* �}�E�X�{�^����������Ă��邩
	* @param (mouse) �}�E�X�{�^���A��`�ς݂̗񋓌^�Ŏw��
	*/
	virtual bool isMouseButtonRelease(EMouseButton mouse) = 0;

	/**
	* @fn
	* �}�E�X�{�^����������Ă��邩
	* @param (mouse) �}�E�X�{�^���A��`�ς݂̗񋓌^�Ŏw��
	*/
	virtual const Vector2& getMousePosition() = 0;

	/**
	* @fn
	* �p�b�h�{�^���������ꂽ�u�Ԃ��擾
	* @param (button) �p�b�h�{�^���A��`�ς݂̗񋓌^�Ŏw��
	*/
	virtual bool isButtonDown(const EPlayerIndex& index, const GamePadButton button) = 0;

	/**
	* @fn
	* �p�b�h�{�^����������Ă��邩���擾
	* @param (button) �p�b�h�{�^���A��`�ς݂̗񋓌^�Ŏw��
	*/
	virtual bool isButtonPress(const EPlayerIndex& index, const GamePadButton button) = 0;

	/**
	* @fn
	* �p�b�h�{�^���������ꂽ�u�Ԃ��擾
	* @param (button) �p�b�h�{�^���A��`�ς݂̗񋓌^�Ŏw��
	*/
	virtual bool isButtonUp(const EPlayerIndex& index, const GamePadButton button) = 0;

	/**
	* @fn
	* �p�b�h�{�^����������Ă��邩
	* @param (button) �p�b�h�{�^���A��`�ς݂̗񋓌^�Ŏw��
	*/
	virtual bool isButtonRelease(const EPlayerIndex& index, const GamePadButton button) = 0;

	/**
	* @fn
	* �p�b�h�̍��X�e�B�b�N�̓��͗ʂ��擾
	*/
	virtual Vector2& getLeftStick(const EPlayerIndex& index) = 0;

	/**
	* @fn
	* �p�b�h�̉E�X�e�B�b�N�̓��͗ʂ��擾
	*/
	virtual Vector2& getRightStick(const EPlayerIndex& index) = 0;

	/**
	* @fn
	* �p�b�h�̍��g���K�[�̓��͗ʂ��擾
	*/
	virtual float getLeftTrigger(const EPlayerIndex& index) = 0;
	
	/**
	* @fn
	* �p�b�h�̍��g���K�[�̓��͗ʂ��擾
	*/
	virtual float getRightTrigger(const EPlayerIndex& index) = 0;
};

/* End of File *****************************************************/