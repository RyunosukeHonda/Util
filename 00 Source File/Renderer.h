/**
* @file Renderer.h
* @brief 描画機能クラス定義ファイル
* @author Ryunosuke Honda.
*/
#pragma once

#include "IRenderer.h"
#include "Direct3D11.h"
#include "OBJStaticMeshRenderer.h"
#include "FBXHierarchyMeshRenderer.h"
#include "FBXSkinMeshRenderer.h"
#include "SpriteRenderer.h"
#include "QuadRenderer.h"
#include "DirectionalLightDesc.h"

/**
*	描画機能クラス
*	DirectX描画機能や各メッシュ・スプライトの描画クラスの仲介を行う
*/
class Renderer : public IRenderer
{
public:
	/**
	* @fn
	* コンストラクタ
	*/
	Renderer(const HWND& wnd);

	/**
	* @fn
	* デストラクタ
	*/
	~Renderer();

	// IRenderer を介して継承されました
	virtual void setRenderCamera(Camera * camera) override;
	virtual void setDirectionalLight(const DirectionalLightDesc& desc) override;
	virtual void load(const OBJMeshID& id, const LPSTR& fileName) override;
	virtual void load(const FBXHierarchyID& id, const LPSTR& fileName) override;
	virtual void load(const FBXSkinID& id, const LPSTR& fileName) override;
	virtual void load(const TextureID& id, const LPCWSTR& fileName) override;
	virtual void load(const ShaderTextureID & id, const LPCWSTR & fileName) override;
	virtual void render(const OBJStaticMeshRenderDesc * pDesc) override;
	virtual void render(const FBXHierarchyMeshRenderDesc* pDesc) override;
	virtual void render(const FBXSkinMeshRenderDesc * pDesc) override;
	virtual void render(const TextRenderDesc & desc) override;
	virtual void render(const SpriteRenderDesc * pDesc) override;
	virtual void render(const QuadRenderDesc * pDesc) override;
	virtual void render(const UIImageRenderDesc * pDesc) override;
	virtual void render(const UIQuadRenderDesc * pDesc) override;
	virtual void renderExecute() override;
	virtual void renderUI() override;
	virtual void clear() override;
	virtual void present() override;

private:
	/**
	* @fn
	* 初期化処理
	* @brief DirectX11機能や各レンダリングクラスの初期化を行う
	* @detail 生成時に一度だけ自分で呼び出すので他で使用する必要はなし
	*/
	void init();

private:
	//!DirectX機能クラス
	Direct3D11 mDirect3D11;
	//!レンダリングを行うカメラ設定用のポインタ・実体の管理は他で行うのでdeleteなどはしない
	Camera* mpCamera;
	//!OBJスタティックメッシュ描画クラス
	OBJStaticMeshRenderer mOBJStaticMeshRenderer;
	//!FBX階層メッシュ描画クラス
	FBXHierarchyMeshRenderer mFBXHierarchyMeshRenderer;
	//!FBXスキンメッシュ描画クラス
	FBXSkinMeshRenderer mFBXSkinMeshRenderer;
	//!スプライト描画クラス
	SpriteRenderer mSpriteRenderer;
	//!矩形描画クラス
	QuadRenderer mQuadRenderer;
	//!平行光源
	DirectionalLightDesc mLight;

	//!UI描画用ビューポート
	D3D11_VIEWPORT mUIPort;
	//!UI座標系、ビュー行列と平行投影行列をかけ合わせた行列
	Matrix4x4 mUIMatrix;
};

/****** End of File *****************************************************/
