/**
* @file IGameDevice.h
* @brief �Q�[���f�o�C�X����C���^�[�t�F�[�X
* @author Ryunosuke Honda.
*/
#pragma once

#include <combaseapi.h>

//�����_���[�C���^�t�F�[�X
class IRenderer;

//���̓C���^�t�F�[�X
class IInput;

/**
*	�Q�[���f�o�C�X����C���^�[�t�F�[�X
*/
class IGameDevice
{
public:
	/**
	* @fn
	* ���z�f�X�g���N�^
	*/
	virtual ~IGameDevice(){}

	/**
	* @fn
	* �����_���[�擾
	*/
	virtual IRenderer& renderer() = 0;

	/**
	* @fn
	* ���̓N���X�擾
	*/
	virtual IInput& input() = 0;
};

/****** End of File *****************************************************/