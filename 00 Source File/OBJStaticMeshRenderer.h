/**
* @file OBJStaticMeshRenderer.h
* @brief OBJ形式のスタティックメッシュ描画クラス定義ファイル
* @author Ryunosuke Honda.
*/
#pragma once

#include "Direct3D11.h"
#include "OBJStaticMeshID.h"
#include "OBJStaticMesh.h"
#include "OBJStaticMeshRenderDesc.h"
#include "ResourceRenderer.h"

/**
*	OBJ形式のスタティックメッシュ描画クラス
*/
class OBJStaticMeshRenderer : public ResourceRenderer<OBJMeshID, OBJStaticMesh, OBJStaticMeshRenderDesc>
{
public:
	/**
	 * @fn
	 * コンストラクタ
	 */
	OBJStaticMeshRenderer();
	
	/**
	 * @fn
	 * デストラクタ
	 */
	~OBJStaticMeshRenderer();

	/**
	* @fn
	* メッシュの追加
	* @brief ファイルからメッシュを読み込み、コンテナに追加
	* @param (pDevice) DirectX描画機器
	* @param (id) メッシュ管理ID
	* @param (fileName) ファイル名
	* @detail 読み込み及び初期化はメッシュ生成時にメッシュクラスで行う
	*/
	void addMesh(ID3D11Device* pDevice, const OBJMeshID & id, const LPSTR & fileName);

	/// ResourceRenderer を介して継承されました
	virtual HRESULT init(ID3D11Device* pDevice) override;
	virtual void render(ID3D11DeviceContext * pDeviceContext, const Camera * pCamera, const DirectionalLightDesc & light) override;
	virtual void renderTransparent(ID3D11DeviceContext * pDeviceContext, const Camera * pCamera, const DirectionalLightDesc & light) override;

private:
	//!基底クラス命名
	using base = ResourceRenderer;
	//!頂点シェーダー
	ID3D11VertexShader* mpVertexShader;
	//!頂点レイアウト
	ID3D11InputLayout* mpVertexLayout;
	//!ピクセルシェーダー
	ID3D11PixelShader* mpPixelShader;
	//!定数バッファ・描画位置情報用
	ID3D11Buffer* mpConstantBuffer0;
	//!定数バッファ・色情報用
	ID3D11Buffer* mpConstantBuffer1;
};

/* End of File *****************************************************/