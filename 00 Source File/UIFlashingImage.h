/**
* @file UIFlashingImage.h
* @brief UI画像に点滅機能を追加したクラス定義ファイル
* @author Ryunosuke Honda.
*/
#pragma once

#include "UIImageObject.h"
#include "Timer.h"

/**
*	UI画像に点滅機能を追加したクラス
*/
class UIFlashingImage : public UIImageObject
{
public:
	/**
	 * @fn
	 * コンストラクタ
	 */
	UIFlashingImage(const TextureID& id, float time);

	/**
	 * @fn
	 * デストラクタ
	 */
	virtual ~UIFlashingImage();

	virtual void draw(IRenderer& renderer) override;

protected:
	//!点滅間隔計測タイマー
	Timer mTimer;
	//!表示フラグ
	bool mEnable;

private:
	using base = UIImageObject;
};

/* End of File *****************************************************/