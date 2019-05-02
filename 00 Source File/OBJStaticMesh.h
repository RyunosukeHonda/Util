/**
* @file OBJStaticMesh.h
* @brief OBJ形式のスタティックメッシュクラス定義ファイル
* @author Ryunosuke Honda.
*/
#pragma once

#include "Base.h"

class Camera;

struct MyMaterial;
struct MyVertex;
struct OBJStaticMeshRenderDesc;

/**
*	OBJ形式のスタティックメッシュクラス
*/
class OBJStaticMesh : public CElement
{
public:
	/**
	* @fn
	* コンストラクタ
	* @param (pDevice) 描画デバイス
	* @param (fileName) 読み込むファイル名
	*/
	OBJStaticMesh(ID3D11Device* pDevice, LPSTR fileName);

	/**
	* @fn
	* デストラクタ
	*/
	~OBJStaticMesh();

	void render(ID3D11DeviceContext* pDeviceContext, ID3D11Buffer* mpConstantBuffer1, const OBJStaticMeshRenderDesc* pDesc);

private:
	/**
	* @fn
	* メッシュ初期化
	* @return 正常に終了したか
	*/
	HRESULT InitStaticMesh(ID3D11Device* pDevice, LPSTR FileName);

	/**
	* @fn
	* ファイルからマテリアルを読み込む
	* @return 正常に終了したか
	*/
	HRESULT LoadMaterialFromFile(ID3D11Device* pDevice, LPSTR FileName, MyMaterial** ppMaterial, DWORD* pdwNUmMaterial);

private:
	//!マテリアル内の面の数
	DWORD* mdwNumFaceInMaterial;
	//! バーテックスバッファー
	ID3D11Buffer* mpVertexBuffer;
	//! インデックスバッファー
	ID3D11Buffer** mppIndexBuffer;
	int** mppiVertexIndex;
	//! マテリアル数
	DWORD mdwNumMaterial;
	//! 使用マテリアル(配列)
	MyMaterial* mpMaterial;
	//!頂点構造体
	MyVertex* mpvVertexBuffer;
	//!サンプルリニア
	ID3D11SamplerState* mpSampleLinear;
};

/****** End of File *****************************************************/
