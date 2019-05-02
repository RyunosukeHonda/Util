/**
* @file Field.h
* @brief ステージモデルクラス定義ファイル
* @author Ryunosuke Honda.
*/
#pragma once

#include "PlaneCollider.h"
#include "IObject.h"
#include "OBJStaticMeshRenderDesc.h"

/**
*	ステージモデルクラス
*/
class Field : public PlaneCollider, public IObject
{
public:
	/**
	 * @fn
	 * デフォルトコンストラクタ
	 */
	Field();

	/**
	 * @fn
	 * デストラクタ
	 */
	~Field();

	/**
	* @fn
	* ステージ描画
	* @param (renderer) 描画クラス
	*/
	virtual void draw(IRenderer& renderer) override;

private:
	using base = PlaneCollider;
	//!モデル描画記述子
	OBJStaticMeshRenderDesc mDesc;
};

/* End of File *****************************************************/