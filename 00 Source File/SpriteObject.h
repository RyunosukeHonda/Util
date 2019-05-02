/**
* @file SpriteObject.h
* @brief スプライトオブジェクトクラス定義ファイル
* @author Ryunosuke Honda.
*/
#pragma once

#include "IObject.h"
#include "Transform.h"
#include "TextureID.h"
#include "SpriteRenderDesc.h"

/**
*	スプライトオブジェクトクラス	
*	トランスフォーム、画像IDなど
*	描画に必要な情報をまとめたクラス
*/
class SpriteObject : public Transform, public IObject
{
public:
	/**
	* @fn
	* コンストラクタ
	* @param (id) 画像ID
	*/
	SpriteObject(const TextureID& id);

	/**
	 * @fn
	 * デストラクタ
	 */
	~SpriteObject();

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

private:
	//!描画記述子
	SpriteRenderDesc mDesc;
};

/* End of File *****************************************************/