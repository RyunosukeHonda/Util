/**
* @file Singleton.h
* @brief �p�����^���w�肷�邱�ƂŃN���X���V���O���g���ɂ���N���X
* @author Ryunosuke Honda.
*/
#pragma once

#include "BASE.h"
#include <memory>

/**
*	�V���O���g�����N���X
*/
template <class T>
class Singleton
{
public:
	/**
	* @fn
	* �C���X�^���X�̎擾
	* @return �V���O���g���������N���X�̎Q��
	*/
	static T& instance()
	{
		static typename T::SingletonPointer s_singleton(T::createInstance());

		return getReference(s_singleton);
	}

private:
	using SingletonPointer = unique_ptr<T>;

	/**
	* @fn
	* �C���X�^���X����
	* @return ���������C���X�^���X
	*/
	inline static T *createInstance() { return new T(); }

	/**
	* @fn
	* �Q�Ƃ̎擾
	* @param (ptr) �V���O���g��������N���X�̃|�C���^
	* @return �V���O���g���������N���X�̎Q��
	*/
	inline static T &getReference(const SingletonPointer &ptr) { return *ptr; }

protected:
	Singleton() {}

private:
	Singleton(const Singleton &) = delete;
	Singleton& operator=(const Singleton &) = delete;
	Singleton(Singleton &&) = delete;
	Singleton& operator=(Singleton &&) = delete;
};

/****** End of File *****************************************************/