/**
* @file StateMachineTemplate.h
* @brief ステートパターンテンプレートクラス
* @author Ryunosuke Honda.
*/
#pragma once

#include "Manager.h"
#include "IState.h"

/**
*	ステートパターンテンプレートクラス
*	状態の登録、終了時の状態変更等を行う
*	ステート終了判定を派生クラスで呼び出さなければならないので注意
*	(K) ステートマップのキー・列挙型を推奨
*	(V = IState) 登録するステート・IStateを継承していることが条件
*/
template<class K, class V = IState<K>>
class StateMachineTemplate : public Manager<K, V>
{
public:
	/**
	 * @fn
	 * デフォルトコンストラクタ
	 */
	StateMachineTemplate() {}

	/**
	 * @fn
	 * デストラクタ
	 */
	virtual ~StateMachineTemplate() {}

	/*
	* @fn
	* 初期化
	* @brief 指定した状態に変更する
	* changeを呼ばれるのは好ましくないため
	* 最初の一度のみ利用者に呼び出してもらう
	* @param (name)  キー：ステート名
	*/
	void initState(const K name)
	{
		change(name);
	}

	bool isEnd()
	{

	}

protected:
	/*
	* @fn
	* ステート変更
	* @param (name)  キー：ステート名
	* @brief 連想配列から引数のシーンを取り出し、
	*        現在のシーンに登録する
	*/
	void change(K name)
	{
		if (mCurrentState != nullptr)
		{
			//ステート終了時処理
			mCurrentState->shutdown();
		}
		//次のステートを取得し、初期化
		mCurrentState = get(name);
		mCurrentState->init();
	}

	/*
	* @fn
	* ステート終了チェック
	* @brief 派生先のupdateなどで呼び出さないとステートが変更されないので注意
	*/
	void stateEndCheck()
	{
		//シーンが終了していたら次のシーンへ遷移
		if (mCurrentState->isEnd())
		{
			change(mCurrentState->next());
		}
	}

protected:
	//!要素ポインタ命名
	using IStatePointer = ProductPointer;
	//!現在ステート
	IStatePointer mCurrentState;
};

/* End of File *****************************************************/