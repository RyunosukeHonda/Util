/**
* @file IState.h
* @brief ステートパターンの要素に必要なステートの最低限機能インターフェース
* @author Ryunosuke Honda.
*/
#pragma once

/**
*	ステートパターンの要素に必要なステートの最低限機能インターフェース
*/
template <class E>
class IState
{
public:
	/**
	 * @fn
	 * 仮想デストラクタ
	 */
	virtual ~IState() {}

	/**
	* @fn
	* 初期化
	*/
	virtual void init() = 0;

	/**
	* @fn
	* シーン終了時処理
	*/
	virtual void shutdown() = 0;

	/**
	* @fn
	* 終了判定
	* @return シーンが終了したかどうか
	*/
	virtual bool isEnd() = 0;

	/**
	* @fn
	* 次のシーンを返す
	* @return 移動先のシーン列挙
	*/
	virtual E next() = 0;
};

/* End of File *****************************************************/