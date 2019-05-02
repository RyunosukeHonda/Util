/**
* @file Singleton.h
* @brief 継承し型を指定することでクラスをシングルトンにするクラス
* @author Ryunosuke Honda.
*/
#pragma once

#include "BASE.h"
#include <memory>

/**
*	シングルトン化クラス
*/
template <class T>
class Singleton
{
public:
	/**
	* @fn
	* インスタンスの取得
	* @return シングルトン化したクラスの参照
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
	* インスタンス生成
	* @return 生成したインスタンス
	*/
	inline static T *createInstance() { return new T(); }

	/**
	* @fn
	* 参照の取得
	* @param (ptr) シングルトン化するクラスのポインタ
	* @return シングルトン化したクラスの参照
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