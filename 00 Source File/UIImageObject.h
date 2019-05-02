/**
* @file UIImageObject.h
* @brief UI用画像オブジェクトクラス定義ファイル
* @author Ryunosuke Honda.
*/
#pragma once

#include "RectTransform.h"
#include "IObject.h"
#include "TextureID.h"
#include "UIImageRenderDesc.h"

/**
*	UI用画像オブジェクトクラス
*/
class UIImageObject : public RectTransform, public IObject
{
public:
	/**
	 * @fn
	 * コンストラクタ
	 */
	UIImageObject(const TextureID& id);

	/**
	 * @fn
	 * デストラクタ
	 */
	virtual ~UIImageObject();

	/**
	* @fn
	*	テクスチャID設定
	*/
	void setID(const TextureID& id);

	/**
	* @fn
	*	色設定
	* @param (color) 設定する色
	* @detail
	*	シェーダーに送る色を設定するだけなので
	*	対応しているシェーダーのみ色が変わります
	*/
	void setColor(const Color4& color);

	// IObject を介して継承されました
	virtual void draw(IRenderer & renderer) override;

protected:
	//!描画記述子
	UIImageRenderDesc mDesc;
};

/* End of File *****************************************************/