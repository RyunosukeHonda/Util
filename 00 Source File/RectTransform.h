/**
* @file RectTransform.h
* @brief 2次元トランスフォームクラス定義ファイル
* @author Ryunosuke Honda.
*/
#pragma once

#include "Base.h"

/**
*	2次元トランスフォームクラス
*	UI座標系で使用します
*/
class RectTransform
{
public:
	/**
	 * @fn
	 * デフォルトコンストラクタ
	 */
	RectTransform();

	/**
	 * @fn
	 * デストラクタ
	 */
	virtual ~RectTransform();

	/**
	* @fn
	* トランスフォーム情報からワールド行列を算出、格納する関数
	* @param (pOut) 格納する行列のポインタ
	*/
	void makeWorld(Matrix4x4* pOut);

	//!位置
	PROPERTY_READWRITE(Vector2, Position);
	//!回転
	PROPERTY_READWRITE(Vector3, EulerAngle);
	//!スケール
	PROPERTY_READWRITE(Vector2, Scale);
	//!描画優先度・大きいほど手前に表示されます
	PROPERTY_WRITEONLY(int, SortingLayer);
};

/* End of File *****************************************************/