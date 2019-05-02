/**
* @file InputMouse.h
* @brief �}�E�X���͊Ǘ��N���X
* @author Ryunosuke Honda.
*/
#pragma once

#include "Base.h"
#include "EMouseButton.h"

#include <dinput.h>
#include <unordered_map>

/**
*	�}�E�X���̓N���X
*/
class InputMouse : public CElement
{
public:
	/**
	 * @fn
	 * �f�t�H���g�R���X�g���N�^
	 */
	InputMouse(LPDIRECTINPUT8 pDinput, const HWND& hwnd);

	/**
	 * @fn
	 * �f�X�g���N�^
	 */
	~InputMouse();

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
	* �}�E�X�{�^���������ꂽ�u�Ԃ��擾
	* @param (mouse) �}�E�X�{�^���A��`�ς݂̗񋓌^�Ŏw��
	*/
	bool isMouseButtonDown(EMouseButton mouse);

	/**
	* @fn
	* �}�E�X�{�^����������Ă��邩���擾
	* @param (mouse) �}�E�X�{�^���A��`�ς݂̗񋓌^�Ŏw��
	*/
	bool isMouseButtonPress(EMouseButton mouse);

	/**
	* @fn
	* �}�E�X�{�^���������ꂽ�u�Ԃ��擾
	* @param (mouse) �}�E�X�{�^���A��`�ς݂̗񋓌^�Ŏw��
	*/
	bool isMouseButtonUp(EMouseButton mouse);

	/**
	* @fn
	* �}�E�X�{�^����������Ă��邩
	* @param (mouse) �}�E�X�{�^���A��`�ς݂̗񋓌^�Ŏw��
	*/
	bool isMouseButtonRelease(EMouseButton mouse);

private:
	//!�}�E�X���͋@��
	LPDIRECTINPUTDEVICE8 mpMouseDevice;
	//!�}�E�X���i�[�}�b�v�̖���
	using MouseInfoMap = unordered_map<EMouseButton, bool>;
	//!�}�E�X���i�[�}�b�v
	MouseInfoMap mMouseInfo;
	//!�}�E�X���擾�@��
	DIMOUSESTATE2 dims;

	///�ȉ��v���p�e�B
	//!�}�E�X�J�[�\���ړ���
	PROPERTY_READONLY(Vector2, Pos);
};

/* End of File *****************************************************/