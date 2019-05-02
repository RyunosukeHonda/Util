/**
* @file InputGamePad.h
* @brief �Q�[���p�b�h���͋@�\�N���X��`�t�@�C��
* @author Ryunosuke Honda.
*/
#pragma once

#include "Base.h"
#include <vector>
#include <unordered_map>
#include <XInput.h>
#include "EPlayerIndex.h"

#pragma comment(lib,"xinput.lib ")

using GamePadButton = unsigned short;

struct CONTROLER_STATE
{
	XINPUT_STATE state;
	bool bConnected;
};

/**
*	�Q�[���p�b�h���͋@�\�N���X
*/
class InputGamePad
{
private:
	//!�R���g���[���[�ڑ��ő吔
	static const int MAX_CONTROLLERS = 4;  //XInput���F���ł���̂�4�܂�
	//!�X�e�B�b�N�̎��l�̍ő�l
	static const float STICK_MAX;
	//!�g���K�[�̎��ő�l
	static const float TRIGGER_MAX;
public:
	/**
	 * @fn
	 * �f�t�H���g�R���X�g���N�^
	 */
	InputGamePad();

	/**
	 * @fn
	 * �f�X�g���N�^
	 */
	~InputGamePad();

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
	* �p�b�h�{�^���������ꂽ�u�Ԃ��擾
	* @param (button) �p�b�h�{�^���A��`�ς݂̗񋓌^�Ŏw��
	*/
	bool isButtonDown(const EPlayerIndex& index, const GamePadButton button);

	/**
	* @fn
	* �p�b�h�{�^����������Ă��邩���擾
	* @param (button) �p�b�h�{�^���A��`�ς݂̗񋓌^�Ŏw��
	*/
	bool isButtonPress(const EPlayerIndex& index, const GamePadButton button);

	/**
	* @fn
	* �p�b�h�{�^���������ꂽ�u�Ԃ��擾
	* @param (button) �p�b�h�{�^���A��`�ς݂̗񋓌^�Ŏw��
	*/
	bool isButtonUp(const EPlayerIndex& index, const GamePadButton button);

	/**
	* @fn
	* �p�b�h�{�^����������Ă��邩
	* @param (button) �p�b�h�{�^���A��`�ς݂̗񋓌^�Ŏw��
	*/
	bool isButtonRelease(const EPlayerIndex& index, const GamePadButton button);

	Vector2 & getLeftStick(const EPlayerIndex& index);

	Vector2 & getRightStick(const EPlayerIndex& index);

	float getLeftTrigger(const EPlayerIndex& index) const;

	float getRightTrigger(const EPlayerIndex& index) const;

private:
	/**
	* @fn
	* �{�^�����͏�񂪓o�^����Ă��邩�m�F�A����Ă��Ȃ���Γo�^
	* @param (button) �p�b�h�{�^��
	*/
	void checkButtonInfoRegister(const EPlayerIndex& index, const GamePadButton button);

	/**
	* @fn
	* �R���g���[���[�ڑ��m�F
	*/
	void checkConnect();

private:
	//!�Q�[���p�b�h���z��
	CONTROLER_STATE GAME_PAD[MAX_CONTROLLERS];
	//!�{�^�����͏��z��
	vector<WORD> mButtons;
	///�Q�[���p�b�h���ۊǃ}�b�v����
	using GamePadInfoMap = unordered_map<GamePadButton, bool>;
	//!�Q�[���p�b�h���z��
	vector<GamePadInfoMap> mGamePadInfo;
	//!���X�e�B�b�N���
	vector<Vector2> mLeftSticks;
	//!�E�X�e�B�b�N���
	vector<Vector2> mRightSticks;
};

/* End of File *****************************************************/