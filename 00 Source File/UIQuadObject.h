/**
* @file UIQuadObject.h
* @brief UI用矩形オブジェクトクラス定義ファイル
* @author Ryunosuke Honda.
*/
#pragma once

#include "RectTransform.h"
#include "IObject.h"
#include "ShaderTextureID.h"
#include "UIQuadRenderDesc.h"

/**
*	UI用矩形オブジェクトクラス
*/
class UIQuadObject : public RectTransform, public IObject
{
public:
	/**
	* @fn
	* コンストラクタ
	* @param (id) シェーダーリソースID
	*/
	UIQuadObject(const ShaderTextureID& id);

	/**
	 * @fn
	 * デストラクタ
	 */
	virtual ~UIQuadObject();

	/**
	* @fn
	*	色設定
	* @param (color) 設定する色
	* @detail
	*	シェーダーに送る色を設定するだけなので
	*	対応しているシェーダーのみ色が変わります
	*/
	void setColor(Color4& color);

	// IObject を介して継承されました
	virtual void draw(IRenderer & renderer) override;

protected:
	//!描画記述子
	UIQuadRenderDesc mDesc;
};

/* End of File *****************************************************/