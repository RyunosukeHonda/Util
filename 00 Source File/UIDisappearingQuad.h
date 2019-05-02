/**
* @file UIDisappearingQuad.h
* @brief 徐々に消えていく矩形エフェクトクラス定義ファイル
* @author Ryunosuke Honda.
*/
#pragma once

#include "UIQuadObject.h"
#include "Timer.h"

/**
*	徐々に消えていく矩形エフェクトクラス
*/
class UIDisappearingQuad : public UIQuadObject
{
public:
	/**
	* @fn
	* コンストラクタ
	* @param (id) シェーダーID
	* @param (disappearingTime) 消える時間
	*/
	UIDisappearingQuad(const ShaderTextureID& id, float disappearingTime);

	/**
	* @fn
	* デストラクタ
	*/
	~UIDisappearingQuad();

	/**
	* @fn
	* 初期化・タイマーを初期化することで同時に消えていくエフェクトが始まる
	*/
	void init();

	virtual void draw(IRenderer& renderer) override;

private:
	//!基底クラス命名
	using base = UIQuadObject;
	//!消える時間計測タイマー
	Timer mTimer;
	//!初期化時間格納
	float mInitTime;
};

/* End of File *****************************************************/