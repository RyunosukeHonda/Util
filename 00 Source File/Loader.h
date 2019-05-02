/**
* @file Loader.h
* @brief ���\�[�X�ǂݍ��݋@�\�N���X�E�e���v���[�g�d�l�̂���cpp�t�@�C���͂Ȃ�
* @author Ryunosuke Honda.
*/
#pragma once

#include "Base.h"
#include <vector>
#include <string>

template <typename T>
using FileNameContainer = std::vector<T>;

/**
*	���\�[�X�ǂݍ��݋@�\�N���X
*	T = �t�@�C�����̌^���w��
*/
template <typename T>
class Loader
{
public:
	/**
	* @fn
	* �R���X�g���N�^
	* @param (data) �t�@�C�����R���e�i
	*/
	Loader(FileNameContainer<T>& data);

	/**
	* @fn
	* ���z�f�X�g���N�^
	*/
	virtual ~Loader() {}

	/**
	* @fn
	* �X�V����
	*/
	virtual void update() = 0;

	/**
	* @fn
	* ���݉��܂œǂݍ��񂾂�
	*/
	int count();

	/**
	* @fn
	* �o�^����Ă��鐔
	*/
	int regMaxNumber();
	
	/**
	* @fn
	* �ǂݍ��݂��I��������
	*/
	bool isEnd();

protected:
	//!�ǂݍ��ރt�@�C�����Q
	FileNameContainer<T>& mData;
	//!���݂̓ǂݍ��ݐ�
	int mCurrentRead;
	//!�I���t���O
	bool mEndFlag;
};

template<typename T>
Loader<T>::Loader(FileNameContainer<T> & data) :
	mData(data),
	mCurrentRead(0),
	mEndFlag(false)
{
}

template<typename T>
int Loader<T>::count()
{
	return mCurrentRead;
}

template<typename T>
int Loader<T>::regMaxNumber()
{
	return mData.size();
}

template<typename T>
bool Loader<T>::isEnd()
{
	return mEndFlag;
}

/****** End of File *****************************************************/