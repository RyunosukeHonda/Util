/**
* @file SpriteRenderer.h
* @brief スプライト管理クラス定義ファイル
* @author Ryunosuke Honda.
*/
#pragma once

#include "Sprite.h"
#include "TextureID.h"
#include "SpriteRenderDesc.h"
#include "ResourceRenderer.h"

struct UIImageRenderDesc;

/**
*	スプライト管理クラス
*	スプライトに使用するリソースはUIのイメージにもなりうるため
*	UI用の描画関数・記述子データ配列も持つ
*/
class SpriteRenderer : public ResourceRenderer<TextureID, Sprite, SpriteRenderDesc>
{
public:
	/**
	 * @fn
	 * デフォルトコンストラクタ
	 */
	SpriteRenderer();

	/**
	 * @fn
	 * デストラクタ
	 */
	~SpriteRenderer();

	/**
	* @fn
	* スプライトの追加
	* @brief ファイルからテクスチャを読み込み、コンテナに追加
	* @param (pDevice) DirectX描画機器
	* @param (id) テクスチャ管理ID
	* @param (fileName) ファイル名
	* @detail 読み込み及び初期化はスプライト生成時にSpriteクラスで行う
	*/
	void addSprite(ID3D11Device* pDevice, const TextureID & id, const LPCWSTR & fileName);

	/**
	* @fn
	* UI画像描画記述子の登録
	* @brief アルファ値によって登録先を分岐する
	* @param (pDesc) UI画像描画記述子
	*/
	void registerUIData(const UIImageRenderDesc* pDesc);

	/**
	* @fn
	* UI画像描画実行
	* @param (pDeviceContext) DirectX描画機器
	* @param (UIMatrix) UI座標系
	*/
	void renderUI(ID3D11DeviceContext* pDeviceContext, const Matrix4x4& UIMatrix);

	/**
	* @fn
	* UI画像描画記述子の登録
	* @param (pDesc) UI画像描画記述子
	* @param (UIMatrix) UI座標系
	*/
	void renderTransparentUI(ID3D11DeviceContext* pDeviceContext, const Matrix4x4& UIMatrix);

	/**
	* @fn
	* 登録データのクリア
	*/
	void clearUI();

	/// ResourceRenderer を介して継承されました
	HRESULT init(ID3D11Device* pDevice) override;
	void render(ID3D11DeviceContext* pDeviceContext, const Camera* pCamera, const DirectionalLightDesc& light) override;
	void renderTransparent(ID3D11DeviceContext* pDeviceContext, const Camera* pCamera, const DirectionalLightDesc& light) override;

private:
	/**
	* @fn
	* 描画設定の初期化
	*/
	void initRenderConfig(ID3D11DeviceContext* pDeviceContext);

	/**
	* @fn
	* スプライトの描画実行
	*/
	void renderSprite(const SpriteRenderDesc* pDesc, ID3D11DeviceContext* pDeviceContext, const Camera* pCamera, const DirectionalLightDesc& light);

	/**
	* @fn
	* UI画像の描画実行
	*/
	void renderUIImage(const UIImageRenderDesc* pDesc, ID3D11DeviceContext* pDeviceContext, const Matrix4x4& UIMatrix);

private:
	//!頂点レイアウト
	ID3D11InputLayout* mpVertexLayout;
	//!バーテックスシェーダー
	ID3D11VertexShader* mpVertexShader;
	//!ピクセルシェーダー
	ID3D11PixelShader* mpPixelShader;
	//!シェーダーに渡す情報バッファ
	ID3D11Buffer* mpConstantBuffer;

	//!記述子コンテナ命名
	using UIData = std::vector<const UIImageRenderDesc*>;
	//!不透過オブジェクトデータ格納コンテナ
	UIData mUIData;
	//!透過オブジェクトデータコンテナ
	UIData mTransparentUIData;
};

/* End of File *****************************************************/