/**
* @file IRenderer.h
* @brief 描画機能インターフェース
* @author Ryunosuke Honda.
*/
#pragma once

#include "Base.h"
#include "OBJStaticMeshID.h"
#include "FBXHierarchyMeshID.h"
#include "FBXSkinMeshID.h"
#include "TextureID.h"
#include "ShaderTextureID.h"

struct OBJStaticMeshRenderDesc;
struct FBXHierarchyMeshRenderDesc;
struct FBXSkinMeshRenderDesc;
struct TextRenderDesc;
struct SpriteRenderDesc;
struct QuadRenderDesc;
struct UIImageRenderDesc;
struct UIQuadRenderDesc;
struct DirectionalLightDesc;

class Camera;

/**
*	レンダラーインターフェース
*/
class IRenderer
{
public:
	/**
	* @fn
	* 仮想デストラクタ
	*/
	virtual ~IRenderer() {};

	/**
	* @fn
	* レンダリングを行うカメラを設定
	* @param (camera) カメラのポインタ
	*/
	virtual void setRenderCamera(Camera* camera) = 0;

	/**
	* @fn
	* レンダリング時に使用する平行光源を設定
	* @param (desc) 平行光源情報記述子
	*/
	virtual void setDirectionalLight(const DirectionalLightDesc& desc) = 0;

	/**
	* @fn
	* リソース読み込み
	* @brief OBJ形式スタティックメッシュのロードを行う
	* @param (id) OBJメッシュ管理ID
	* @param (fileName) 読み込むファイル名
	*/
	virtual void load(const OBJMeshID& id, const LPSTR& fileName) = 0;

	/**
	* @fn
	* リソース読み込み
	* @brief FBX形式スキンメッシュのロードを行う
	* @param (id) FBXスキンメッシュ管理ID
	* @param (fileName) 読み込むファイル名
	*/
	virtual void load(const FBXHierarchyID& id, const LPSTR& fileName) = 0;

	/**
	* @fn
	* リソース読み込み
	* @brief FBX形式スキンメッシュのロードを行う
	* @param (id) FBXスキンメッシュ管理ID
	* @param (fileName) 読み込むファイル名
	*/
	virtual void load(const FBXSkinID& id, const LPSTR& fileName) = 0;

	/**
	* @fn
	* リソース読み込み
	* @brief スプライト(正確には使用するテクスチャ)のロードを行う
	* @param (id) テクスチャ管理ID
	* @param (fileName) 読み込むファイル名
	*/
	virtual void load(const TextureID& id, const LPCWSTR& fileName) = 0;

	/**
	* @fn
	* リソース読み込み
	* @brief 矩形に貼り付けて使用するシェーダーテクスチャのロードを行う
	* @param (id) シェーダーテクスチャ管理ID
	* @param (fileName) 読み込むファイル名
	*/
	virtual void load(const ShaderTextureID& id, const LPCWSTR& fileName) = 0;

	/**
	* @fn
	* 描画
	* @brief OBJ形式のスタティックメッシュの描画を行う
	* @param (desc) OBJメッシュ描画記述子
	* @detail 実際に行うのは描画データの登録だけ
	*/
	virtual void render(const OBJStaticMeshRenderDesc* pDesc) = 0;

	/**
	* @fn
	* 描画
	* @brief FBX形式の階層メッシュの描画を行う
	* @param (pDesc) OBJメッシュ描画記述子
	* @detail 実際に行うのは描画データの登録だけ
	*/
	virtual void render(const FBXHierarchyMeshRenderDesc* pDesc) = 0;

	/**
	* @fn
	* 描画
	* @brief FBX形式のスキンメッシュの描画を行う
	* @param (pDesc) OBJメッシュ描画記述子
	* @detail 実際に行うのは描画データの登録だけ
	*/
	virtual void render(const FBXSkinMeshRenderDesc* pDesc) = 0;

	/**
	* @fn
	* 描画
	* @brief テキストの描画を行う
	* @param (desc) テキスト描画記述子
	* @detail DirectX10標準機能を使用。重いので主にデバッグ用
	*/
	virtual void render(const TextRenderDesc& desc) = 0;

	/**
	* @fn
	* 描画
	* @brief スプライトの描画を行う
	* @param (pDesc) スプライト描画記述子
	* @detail 実際に行うのは描画データの登録だけ
	*/
	virtual void render(const SpriteRenderDesc* pDesc) = 0;

	/**
	* @fn
	* 描画
	* @brief 四角家ポリゴン(シェーダーテクスチャ付与)の描画を行う
	* @param (pDesc) 矩形描画記述子
	* @detail 実際に行うのは描画データの登録だけ
	*/
	virtual void render(const QuadRenderDesc* pDesc) = 0;

	/**
	* @fn
	* 描画
	* @brief UI座標系で画像の描画を行う
	* @param (pDesc) UI画像描画記述子
	* @detail 実際に行うのは描画データの登録だけ
	*/
	virtual void render(const UIImageRenderDesc* pDesc) = 0;

	/**
	* @fn
	* 描画
	* @brief UI座標系でシェーダーを貼り付けた矩形の描画を行う
	* @param (pDesc) UI矩形描画記述子
	* @detail 実際に行うのは描画データの登録だけ
	*/
	virtual void render(const UIQuadRenderDesc* pDesc) = 0;

	/**
	* @fn
	* 描画実行
	* @brief 登録された描画データを実際に描画する
	*/
	virtual void renderExecute() = 0;

	/**
	* @fn
	* UI描画実行
	* @brief 登録されたUI描画データを実際に描画する
	* @detail モデル描画が全て終わったあとに実行する
	*/
	virtual void renderUI() = 0;

	/**
	* @fn
	* 画面クリア
	*/
	virtual void clear() = 0;

	/**
	* @fn
	* 画面更新（バックバッファをフロントバッファに）
	*/
	virtual void present() = 0;
};

/****** End of File *****************************************************/
