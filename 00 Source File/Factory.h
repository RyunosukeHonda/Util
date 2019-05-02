/**
* @file Factory.h
* @brief ファクトリーパターンのベースクラス
* @detail 複製可能な製品を管理するため、マネージャとは区別して定義
* @author Ryunosuke Honda.
*/
#pragma once

#include <memory>
#include <unordered_map>

/**
*	ファクトリーパターンベースクラス
*/
template<class K, class V>
class Factory
{
	///継承先で改名できるようprotected
protected:
	///要素を格納する連想配列
	using ProductContainer = unordered_map<K, V*>;

public:
	/**
	* @fn
	* クリーン処理
	* @brief 登録した製品を安全に破棄
	*/
	void clear()
	{
		ProductContainer::iterator i = mProductContainer.begin();
		while (i != mProductContainer.end()) {
			delete i->second;
			++i;
		}
	}

	/**
	* @fn
	* 製品の登録
	* @brief Key"K", Value"V
	* @param (name) キーの名前
	* @param (product) 登録する製品
	*/
	void add(const K& name, V* product)
	{
		//既にキーが登録されていないかチェック、
		//登録されていたらキーをコンソールに出力しリターン
		if (isRegister(name))
		{
			cout << "キーが二重に登録されています" << endl;
			return;
		}

		mProductContainer[name] = product;
	}

	/**
	* @fn
	* 登録した製品をキーを参照して生産
	* @param (name) キーの名前
	* @return 製品の複製
	*/
	V* create(const K& name)
	{
		return mProductContainer[name]->clone();
	}

private:
	/**
	* @fn
	* キーが既に登録されているか判定
	* @param (name) キーの名前
	* @return 既に登録されていればtrue
	*/
	bool isRegister(const K& name)
	{
		return mProductContainer.count(name) != 0;
	}

	//!製品コンテナ
	ProductContainer mProductContainer;					
};

/****** EOF *****************************************************/