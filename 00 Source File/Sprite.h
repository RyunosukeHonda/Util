/**
* @file Sprite.h
* @brief スプライトクラス定義ファイル
* @author Ryunosuke Honda.
*/
#pragma once

#include "Base.h"

/**
*	スプライトクラス
*/
class Sprite : public CElement
{
public:
	/**
	* @fn
	* コンストラクタ
	* @param (pDevice) 描画デバイス
	* @param (fileName) 読み込むファイル名
	*/
	Sprite(ID3D11Device* pDevice, LPCWSTR fileName);

	/**
	 * @fn
	 * デストラクタ
	 */
	~Sprite();

	/**
	* @fn
	* 描画
	* @param (pDeviceContext) 描画デバイス
	*/
	void render(ID3D11DeviceContext* pDeviceContext);

private:
	/**
	* @fn
	* 初期化
	* @param (pDevice) 描画デバイス
	* @param (fileName) 読み込むファイル名
	*/
	void init(ID3D11Device* pDevice, LPCWSTR fileName);

private:
	//!頂点バッファ
	ID3D11Buffer* mpVertexBuffer;
	//!テクスチャーのサンプラー
	ID3D11SamplerState* mpSampleLinear;
	//!テクスチャー
	ID3D11ShaderResourceView* mpTexture;
};

/* End of File *****************************************************/