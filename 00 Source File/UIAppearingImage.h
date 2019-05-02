/**
* @file UIAppearingImage.h
* @brief 徐々に現れる画像エフェクトクラス定義ファイル
* @author Ryunosuke Honda.
*/
#pragma once

#include "UIImageObject.h"
#include "Timer.h"

/**
*	徐々に現れる画像エフェクトクラス定義ファイル
*/
class UIAppearingImage : public UIImageObject
{
public:
	/**
	* @fn
	* コンストラクタ
	* @param (id) テクスチャID
	* @param (appearingTime) 現れる時間
	*/
	UIAppearingImage(const TextureID& id, float appearingTime);

	/**
	 * @fn
	 * デストラクタ
	 */
	~UIAppearingImage();

	/**
	* @fn
	* 初期化・タイマーを初期化することで同時に消えていくエフェクトが始まる
	*/
	void init();

	virtual void draw(IRenderer& renderer) override;

private:
	//!基底クラス命名
	using base = UIImageObject;
	//!消える時間計測タイマー
	Timer mTimer;
	//!初期化時間格納
	float mInitTime;
};

/* End of File *****************************************************/