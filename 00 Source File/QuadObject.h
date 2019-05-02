/**
* @file QuadObject.h
* @brief 矩形オブジェクトクラス定義ファイル
* @author Ryunosuke Honda.
*/
#pragma once

#include "IObject.h"
#include "Transform.h"
#include "ShaderTextureID.h"
#include "QuadRenderDesc.h"

/**
*	矩形オブジェクトクラス
*	トランスフォーム、シェーダーIDなど
*	描画に必要な情報をまとめたクラス
*/
class QuadObject : public Transform, public IObject
{
public:
	/**
	* @fn
	* コンストラクタ
	* @param (id) シェーダーID
	*/
	QuadObject(const ShaderTextureID& id);
	
	/**
	 * @fn
	 * デストラクタ
	 */
	~QuadObject();

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
	QuadRenderDesc mDesc;
};

/* End of File *****************************************************/