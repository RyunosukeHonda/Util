/**
* @file ObjectManager.h
* @brief IObject管理クラス定義ファイル
* @author Ryunosuke Honda.
*/
#pragma once

#include "BASE.h"
#include "EntityManager.h"

class IObject;
class IRenderer;

/**
*	IObject管理クラス	
*	更新などの処理が必要ないオブジェクトの描画を行います
*/
class ObjectManager
{
public:
	/**
	 * @fn
	 * デフォルトコンストラクタ
	 */
	ObjectManager();
	
	/**
	 * @fn
	 * デストラクタ
	 */
	~ObjectManager();

	/**
	* @fn
	* オブジェクト追加
	* @param (pObj) 追加する要素のポインタ
	*/
	void add(IObject* pObj);

	/**
	* @fn
	* 全要素描画
	* @param (renderer) レンダラー 
	*/
	void draw(IRenderer& renderer);

	/**
	* @fn
	* 全要素削除
	*/
	void clear();

private:
	EntityManager<IObject*> mObjList;
};

/* End of File *****************************************************/