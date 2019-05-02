/**
* @file IAddable.h
* @brief 管理要素追加機能仲介インターフェース
* @author Ryunosuke Honda.
*/
#pragma once

/**
*	管理要素追加機能仲介インターフェース
*/
template<class T>
class IAddable
{
public:
	/**
	 * @fn
	 * デストラクタ
	 */
	virtual ~IAddable() {};

	/**
	* @fn
	* 要素追加
	* @param (value) 追加する要素のポインタ
	*/
	virtual void add(T* value) = 0;
};

/* End of File *****************************************************/