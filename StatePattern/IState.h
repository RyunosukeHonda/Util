/**
* @file IState.h
* @brief �X�e�[�g�p�^�[���̗v�f�ɕK�v�ȃX�e�[�g�̍Œ���@�\�C���^�[�t�F�[�X
* @author Ryunosuke Honda.
*/
#pragma once

/**
*	�X�e�[�g�p�^�[���̗v�f�ɕK�v�ȃX�e�[�g�̍Œ���@�\�C���^�[�t�F�[�X
*/
template <class E>
class IState
{
public:
	/**
	 * @fn
	 * ���z�f�X�g���N�^
	 */
	virtual ~IState() {}

	/**
	* @fn
	* ������
	*/
	virtual void init() = 0;

	/**
	* @fn
	* �V�[���I��������
	*/
	virtual void shutdown() = 0;

	/**
	* @fn
	* �I������
	* @return �V�[�����I���������ǂ���
	*/
	virtual bool isEnd() = 0;

	/**
	* @fn
	* ���̃V�[����Ԃ�
	* @return �ړ���̃V�[����
	*/
	virtual E next() = 0;
};

/* End of File *****************************************************/