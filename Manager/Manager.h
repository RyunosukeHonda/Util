/**
* @file Manager.h
* @brief 連想配列を管理するマネージャーのベースクラス
* @detail 複製されたくない要素を管理するため、ファクトリーとは区別して定義
* @author Ryunosuke Honda.
*/
#pragma once

#include <unordered_map>
#include <memory>

/**
*	マネージャーベースクラス
*/
template<class K, class V>
class Manager
{
	///継承先で改名できるようprotected
protected:
	///要素ポインタ
	using ProductPointer = shared_ptr<V>;
	///要素を格納する連想配列
	using ProductContainer = unordered_map<K, ProductPointer>;

public:
	/**
	* @fn
	* クリーン処理
	* @brief 登録した要素を安全に破棄
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
	* 要素の登録
	* @brief Key"K", Value"V
	* @param (name) キーの名前
	* @param (product) 登録する要素
	* @detail 要素は自動的にshared_pointerに変換されます
	*/
	void add(const K& name, V* product)
	{
		//既にキーが登録されていないかチェック、
		//登録されていたらキーをコンソールに出力しリターン
		if (isRegister(name))
		{
			Debug::log("キーが二重に登録されています");
			return;
		}

		mProductContainer[name] = ProductPointer(product);
	}

	/**
	* @fn
	* 登録した要素の参照を取得
	* @param (name) キーの名前
	* @return 要素のポインタ
	* @detail 複製不可または複製の必要がない要素を取得する
	*/
	ProductPointer get(const K& name)
	{
		return mProductContainer[name];
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

private:
	//!要素コンテナ
	ProductContainer mProductContainer;
};

/****** EOF *****************************************************/