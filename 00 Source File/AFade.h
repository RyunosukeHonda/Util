/**
* @file AFade.h
* @brief �t�F�[�h�������N���X��`�t�@�C��
* @author Ryunosuke Honda.
*/
#pragma once

#include "Timer.h"
#include "UIQuadObject.h"

/**
*	�t�F�[�h�������N���X
*	�p������draw�̕��@��ύX��
*	�t�F�[�h�C���A�A�E�g����������
*	���e�͒P���ɍ��h��e�N�X�`���̃A���t�@�l���^�C�}�[�ő��삷�邾��
*/
class AFade
{
public:
	/**
	* @fn
	*	�R���X�g���N�^
	*/
	AFade();

	/**
	* @fn
	*	���z�f�X�g���N�^
	*/
	virtual ~AFade() {}

	/**
	* @fn
	* ������
	*/
	void init();

	/**
	* @fn
	* �t�F�[�h�̎��s�Bsecond�b�Ԃŏ������s���܂�
	* @param (second) �t�F�[�h���鎞��(�b)
	*/
	void start(float second);

	/**
	* @fn
	* �t�F�[�h�������I��

	*/
	void forcedEnd();

	/**
	* @fn
	* �t�F�[�h���I���������ǂ���
	*/
	bool isEnd();

	/**
	* @fn
	* �X�V�E�^�C�}�[��i�߂�
	*/
	void update();

	/**
	* @fn
	* �`��
	* @param (renderer) �����_���[
	*/
	virtual void draw(IRenderer& renderer) = 0;

protected:
	//!�^�C�}�[
	Timer mTimer;
	//!�ғ�����
	bool mIsWorking;
	//!�P�F�w�i
	UIQuadObject mBG;
};

/****** End of File *****************************************************/
