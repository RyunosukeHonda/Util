/**
* @file FBXSkinMeshRenderer.h
* @brief FBX形式のスキンメッシュ管理クラス定義ファイル
* @author Ryunosuke Honda.
*/
#pragma once

#include "FBXSkinMesh.h"
#include "FBXSkinMeshID.h"
#include "FBXSkinMeshRenderDesc.h"
#include "ResourceRenderer.h"

/**
*	FBX形式のスキンメッシュ管理クラス
*/
class FBXSkinMeshRenderer : public ResourceRenderer<FBXSkinID, FBXSkinMesh, FBXSkinMeshRenderDesc>
{
public:
	/**
	* @fn
	* コンストラクタ
	*/
	FBXSkinMeshRenderer();

	/**
	* @fn
	* デストラクタ
	*/
	~FBXSkinMeshRenderer();

	/**
	* @fn
	* メッシュの追加
	* @brief ファイルからメッシュを読み込み、コンテナに追加
	* @param (pDevice) DirectX描画機器
	* @param (id) メッシュ管理ID
	* @param (fileName) ファイル名
	* @detail 読み込み及び初期化はメッシュ生成時にメッシュクラスで行う
	*/
	void addMesh(ID3D11Device* pDevice, const FBXSkinID & id, const LPSTR & fileName);

	/// ResourceRenderer を介して継承されました
	virtual HRESULT init(ID3D11Device* pDevice) override;
	virtual void render(ID3D11DeviceContext* pDeviceContext, const Camera* pCamera, const DirectionalLightDesc & light) override;
	virtual void renderTransparent(ID3D11DeviceContext* pDeviceContext, const Camera* pCamera, const DirectionalLightDesc & light) override;

private:
	using base = ResourceRenderer;

	//↓モデルの種類ごと(モデルの構造が全て同一ならアプリにひとつ）
	ID3D11InputLayout* mpVertexLayout;
	ID3D11VertexShader* mpVertexShader;
	ID3D11PixelShader* mpPixelShader;
	ID3D11Buffer* mpConstantBuffer0;
	ID3D11Buffer* mpConstantBuffer1;
	ID3D11Buffer* mpConstantBuffer2;
};

/* End of File *****************************************************/