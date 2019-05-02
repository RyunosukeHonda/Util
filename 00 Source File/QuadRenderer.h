/**
* @file QuadRenderer.h
* @brief 四角形ポリゴン描画クラス定義ファイル
* @author Ryunosuke Honda.
*/
#pragma once

#include "ResourceRenderer.h"
#include "ShaderTextureID.h"
#include "Quad.h"
#include "QuadRenderDesc.h"

struct UIQuadRenderDesc;

/**
*	四角形ポリゴン描画クラス
*	単純な四角形ポリゴンに任意のシェーダーを貼り付けた
*	2DEffectを描画します
*	また矩形に使用するシェーダーリソースはUIのイメージにもなりうるため
*	UI用の描画関数・記述子データ配列も持つ
*/
class QuadRenderer : public ResourceRenderer<ShaderTextureID, Quad, QuadRenderDesc>
{
public:
	/**
	 * @fn
	 * デフォルトコンストラクタ
	 */
	QuadRenderer();

	/**
	 * @fn
	 * デストラクタ
	 */
	~QuadRenderer();

	/**
	* @fn
	* メッシュの追加
	* @brief ファイルからメッシュを読み込み、コンテナに追加
	* @param (pDevice) DirectX描画機器
	* @param (id) メッシュ管理ID
	* @param (fileName) ファイル名
	* @detail 読み込み及び初期化はメッシュ生成時にメッシュクラスで行う
	*/
	void addQuad(ID3D11Device* pDevice, const ShaderTextureID & id, const LPCWSTR & fileName);

	/**
	* @fn
	* UI画像描画記述子の登録
	* @brief アルファ値によって登録先を分岐する
	* @param (pDesc) UI画像描画記述子
	*/
	void registerUIData(const UIQuadRenderDesc* pDesc);

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

	// ResourceRenderer を介して継承されました
	virtual HRESULT init(ID3D11Device * pDevice) override;
	virtual void render(ID3D11DeviceContext * pDeviceContext, const Camera * pCamera, const DirectionalLightDesc & light) override;
	virtual void renderTransparent(ID3D11DeviceContext * pDeviceContext, const Camera * pCamera, const DirectionalLightDesc & light) override;

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
	void renderQuad(const QuadRenderDesc* pDesc, ID3D11DeviceContext* pDeviceContext, const Camera* pCamera, const DirectionalLightDesc& light);

	/**
	* @fn
	* UI画像の描画実行
	*/
	void renderUIQuad(const UIQuadRenderDesc* pDesc, ID3D11DeviceContext* pDeviceContext, const Matrix4x4& UIMatrix);

private:
	//!シェーダーに渡す情報バッファ
	ID3D11Buffer* mpConstantBuffer; 
	//!記述子コンテナ命名
	using UIData = std::vector<const UIQuadRenderDesc*>;
	//!不透過オブジェクトデータ格納コンテナ
	UIData mUIData;
	//!透過オブジェクトデータコンテナ
	UIData mTransparentUIData;
};

/* End of File *****************************************************/