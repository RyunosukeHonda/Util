/**
* @file InputKey.h
* @brief �L�[���͌��m�N���X��`�t�@�C��
* @author Ryunosuke Honda.
*/
#pragma once

#include "Base.h"

#include <dinput.h>
#include <unordered_map>

/**
*	�L�[���͌��m�N���X
*/
class InputKey : public CElement
{
	///�萔��`
public:
	//!�L�[�ԍ�����
	using KeyCode = int;

public:
	/**
	 * @fn
	 * �f�t�H���g�R���X�g���N�^
	 */
	InputKey(LPDIRECTINPUT8 pDinput, const HWND& hwnd);

	/**
	 * @fn
	 * �f�X�g���N�^
	 */
	~InputKey();

	/**
	* @fn
	* ���͏����X�V
	* @brief ���ۂɓ��͂��擾����
	*/
	void update();

	/**
	* @fn
	* ���͏��X�V
	* @brief �擾�������͏������t���[���Ŏg�p���邽�߂ɕۑ����鏈��
	*/
	void lateUpdate();

	/**
	* @fn
	* �L�[�������ꂽ�u�Ԃ��擾
	* @param (key) �L�[�R�[�h�A��`�ς݂�16�i��[DIK_]�Ŏw��
	*/
	bool isKeyDown(KeyCode key);

	/**
	* @fn
	* �L�[��������Ă��邩���擾
	* @param (key) �L�[�R�[�h�A��`�ς݂�16�i��[DIK_]�Ŏw��
	*/
	bool isKeyPress(KeyCode key);

	/**
	* @fn
	* �L�[�������ꂽ�u�Ԃ��擾
	* @param (key) �L�[�R�[�h�A��`�ς݂�16�i��[DIK_]�Ŏw��
	*/
	bool isKeyUp(KeyCode key);

	/**
	* @fn
	* �L�[��������Ă��邩
	* @param (key) �L�[�R�[�h�A��`�ς݂�16�i��[DIK_]�Ŏw��
	*/
	bool isKeyRelease(KeyCode key);

private:
	/**
	* @fn
	* �L�[��񂪓o�^����Ă��邩�m�F�A����Ă��Ȃ���Γo�^
	* @param (key) �L�[�R�[�h
	*/
	void checkKeyInfoRegister(KeyCode key);

private:
	//!�L�[���i�[�p�z��
	BYTE diks[256];
	//!�L�[���͋@��
	LPDIRECTINPUTDEVICE8 mpKeyDevice;
	//!�L�[���i�[�}�b�v�̖���
	using KeyInfoMap = unordered_map<KeyCode, bool>;
	//!�L�[���i�[�}�b�v
	KeyInfoMap mKeyInfo;
};

/* End of File *****************************************************/