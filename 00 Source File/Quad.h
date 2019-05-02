/**
* @file Quad.h
* @brief 矩形クラス定義ファイル
* @author Ryunosuke Honda.
*/
#pragma once

#include "Base.h"

/**
*	矩形クラス
*	シェーダーテクスチャを貼り付けてエフェクトにする
*/
class Quad : public CElement
{
public:
	/**
	* @fn
	* コンストラクタ
	* @param (pDevice) DirectX描画機器
	* @param (fileName) ファイル名
	*/
	Quad(ID3D11Device* pDevice, LPCWSTR fileName);

	/**
	 * @fn
	 * デストラクタ
	 */
	~Quad();

	/**
	* @fn
	* 描画
	* @param (pDeviceContext) 描画デバイスコンテキスト
	*/
	void render(ID3D11DeviceContext* pDeviceContext);

private:
	/**
	* @fn
	*	初期化処理
	* @param (pDevice) DirectX描画機器
	* @param (fileName) ファイル名
	*/
	void init(ID3D11Device* pDevice, LPCWSTR fileName);

private:
	//!バーテックスシェーダー
	ID3D11VertexShader* mpVertexShader;
	//!ピクセルシェーダー
	ID3D11PixelShader* mpPixelShader;
	//!頂点レイアウト
	ID3D11InputLayout* mpVertexLayout;
	//!頂点バッファ
	ID3D11Buffer* mpVertexBuffer;
};

/* End of File *****************************************************/