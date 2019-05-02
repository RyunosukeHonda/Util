/**
* @file Loader.h
* @brief リソース読み込み機能クラス・テンプレート仕様のためcppファイルはなし
* @author Ryunosuke Honda.
*/
#pragma once

#include "Base.h"
#include <vector>
#include <string>

template <typename T>
using FileNameContainer = std::vector<T>;

/**
*	リソース読み込み機能クラス
*	T = ファイル名の型を指定
*/
template <typename T>
class Loader
{
public:
	/**
	* @fn
	* コンストラクタ
	* @param (data) ファイル名コンテナ
	*/
	Loader(FileNameContainer<T>& data);

	/**
	* @fn
	* 仮想デストラクタ
	*/
	virtual ~Loader() {}

	/**
	* @fn
	* 更新処理
	*/
	virtual void update() = 0;

	/**
	* @fn
	* 現在何個まで読み込んだか
	*/
	int count();

	/**
	* @fn
	* 登録されている数
	*/
	int regMaxNumber();
	
	/**
	* @fn
	* 読み込みが終了したか
	*/
	bool isEnd();

protected:
	//!読み込むファイル名群
	FileNameContainer<T>& mData;
	//!現在の読み込み数
	int mCurrentRead;
	//!終了フラグ
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