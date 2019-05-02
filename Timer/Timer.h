/**
* @file Timer.h
* @brief �ėp�^�C�}�[�N���X(���Z��)��`�t�@�C��
* @author Ryunosuke Honda.
*/
#pragma once

#include "Base.h"

/**
*	�ėp�^�C�}�[�N���X(���Z��)
*	�t���[�����Ȃǂɉe������Ȃ��悤
*	�����ԂŌv�����܂�
*/
class Timer
{
private:
	const int ToDWORD = 1000;
	const float ToSecond = 1.0f / (float)ToDWORD;

public:
	/**
	* @fn
	* �R���X�g���N�^
	* @brief �P�b�ɐݒ�
	*/
	Timer();

	/**
	* @fn
	* �R���X�g���N�^
	* @brief �������Ԑݒ�p
	* @param (limit) �������� 
	*/
	Timer(float limit);

	/**
	* @fn
	* �f�X�g���N�^
	*/
	~Timer();
	
	/**
	* @fn
	* ������
	* @brief �������Ԃ����Z�b�g
	*/
	void init();

	/**
	* @fn
	* ������
	* @brief �������Ԃ�ݒ肵�ă��Z�b�g
	* @param (limit) �ݒ肷�鐧������
	*/
	void init(float limit);

	/**
	* @fn
	* �X�V
	*/
	void update();

	/**
	* @fn
	* �^�C�}�[�I������
	* @return �������Ԃ��o�߂������ǂ���
	*/
	bool isEnd();

	/**
	* @fn
	* ���ݎ��� / �������ԁ@�̊�����Ԃ�
	* @return ���ݎ��� / ��������
	* @detail 0.0f�`1.0f
	*/
	float rate();

	/**
	* @fn
	* ���ݎ��Ԏ擾
	* @return ���ݎ���
	*/
	float getCurrent();

	/**
	* @fn
	* �^�C�}�[�������I������
	*/
	void forcedEnd();
	
private:
	//!��������
	DWORD mLimit;	
	//!���ݎ���
	DWORD mCurrent;	
    //!�J�n���̎������i�[
	DWORD mStart;	
};

/****** End of File *****************************************************/
