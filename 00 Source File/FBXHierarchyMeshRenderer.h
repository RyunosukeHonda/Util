/**
* @file FBXHierarchyMeshRenderer.h
* @brief FBX階層メッシュ描画クラス定義ファイル
* @author Ryunosuke Honda.
*/
#pragma once

#include "Base.h"
#include "FBXHierarchyMeshID.h"
#include "FBXHierarchyMesh.h"
#include "FBXHierarchyMeshRenderDesc.h"
#include "ResourceRenderer.h"



/**
*	FBX階層メッシュ描画クラス
*/
class FBXHierarchyMeshRenderer : public ResourceRenderer<FBXHierarchyID, FBXHierarchyMesh, FBXHierarchyMeshRenderDesc>
{
public:
	/**
	* @fn
	* コンストラクタ
	*/
	FBXHierarchyMeshRenderer();

	/**
	* @fn
	* デストラクタ
	*/
	~FBXHierarchyMeshRenderer();


	/**
	* @fn
	* メッシュの追加
	* @brief ファイルからメッシュを読み込み、コンテナに追加
	* @param (pDevice) DirectX描画機器
	* @param (id) メッシュ管理ID
	* @param (fileName) ファイル名
	* @detail 読み込み及び初期化はメッシュ生成時にメッシュクラスで行う
	*/
	void addMesh(ID3D11Device* pDevice, const FBXHierarchyID & id, const LPSTR& fileName);

	/// ResourceRenderer を介して継承されました
	virtual HRESULT init(ID3D11Device* pDevice) override;
	virtual void render(ID3D11DeviceContext* pDeviceContext, const Camera* pCamera, const DirectionalLightDesc& light) override;
	virtual void renderTransparent(ID3D11DeviceContext* pDeviceContext, const Camera* pCamera, const DirectionalLightDesc& light) override;

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