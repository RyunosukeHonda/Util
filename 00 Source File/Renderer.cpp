/**
* @file Renderer.cpp
* @brief 描画機能クラス実装ファイル
* @author Ryunosuke Honda.
*/
#include "Renderer.h"
#include "Singleton.h"

#include "OBJStaticMeshRenderDesc.h"
#include "TextRenderDesc.h"
#include "SpriteRenderDesc.h"

#include "Camera.h"
#include "Screen.h"

Renderer::Renderer(const HWND& wnd) :
	mDirect3D11(wnd),
	//mpFont(nullptr),
	mOBJStaticMeshRenderer(),
	mFBXSkinMeshRenderer(),
	mSpriteRenderer(),
	mLight()
{
	init();
}

Renderer::~Renderer()
{
	clear();
}
///FIXME wnd
void Renderer::init()
{
	///各描画クラスの初期化

	mOBJStaticMeshRenderer.init(mDirect3D11.getDevicePointer());

	mFBXHierarchyMeshRenderer.init(mDirect3D11.getDevicePointer());

	mFBXSkinMeshRenderer.init(mDirect3D11.getDevicePointer());

	mSpriteRenderer.init(mDirect3D11.getDevicePointer());

	mQuadRenderer.init(mDirect3D11.getDevicePointer());

	//UI用ビューポートの設定
	mUIPort.Width = Screen::WINDOW_WIDTH;
	mUIPort.Height = Screen::WINDOW_HEIGHT;
	mUIPort.MinDepth = 0.0f;
	mUIPort.MaxDepth = 1.0f;
	mUIPort.TopLeftX = 0;
	mUIPort.TopLeftY = 0;

	///UI用座標変換行列の設定
	Matrix4x4 UIView;
	Vector3 eyePt(0.0f, 0.0f, -200); //カメラ（視点）位置
	Vector3 lookPt(0.0f, 0.0f, 0.0f);//注視位置
	Vector3 upVec(0.0f, 1.0f, 0.0f);//上方位置
	D3DXMatrixLookAtLH(&UIView, &eyePt, &lookPt, &upVec);

	Matrix4x4 UIOrtho;
	D3DXMatrixOrthoLH(
		&UIOrtho,
		Screen::WINDOW_WIDTH,
		Screen::WINDOW_HEIGHT,
		Screen::NEAR_,
		Screen::FAR_);

	mUIMatrix = UIView * UIOrtho;
}

void Renderer::renderExecute()
{
	///各リソースの本描画・カリングトリックのため透過オブジェクトのみ二回描画を行います

	//背面カリング状態で全オブジェクトを描画
	mDirect3D11.setCullBack();
	{
		mOBJStaticMeshRenderer.render(mDirect3D11.getDeviceContextPointer(), mpCamera, mLight);
		mFBXHierarchyMeshRenderer.render(mDirect3D11.getDeviceContextPointer(), mpCamera, mLight);
		mFBXSkinMeshRenderer.render(mDirect3D11.getDeviceContextPointer(), mpCamera, mLight);
		mSpriteRenderer.render(mDirect3D11.getDeviceContextPointer(), mpCamera, mLight);
		mQuadRenderer.render(mDirect3D11.getDeviceContextPointer(), mpCamera, mLight);

		mOBJStaticMeshRenderer.renderTransparent(mDirect3D11.getDeviceContextPointer(), mpCamera, mLight);
		mFBXHierarchyMeshRenderer.renderTransparent(mDirect3D11.getDeviceContextPointer(), mpCamera, mLight);
		mFBXSkinMeshRenderer.renderTransparent(mDirect3D11.getDeviceContextPointer(), mpCamera, mLight);
		mSpriteRenderer.renderTransparent(mDirect3D11.getDeviceContextPointer(), mpCamera, mLight);
		mQuadRenderer.renderTransparent(mDirect3D11.getDeviceContextPointer(), mpCamera, mLight);
	}

	//前面カリング状態で透過オブジェクトのみ描画
	mDirect3D11.setCullFront();
	{
		mOBJStaticMeshRenderer.renderTransparent(mDirect3D11.getDeviceContextPointer(), mpCamera, mLight);
		mFBXHierarchyMeshRenderer.renderTransparent(mDirect3D11.getDeviceContextPointer(), mpCamera, mLight);
		mFBXSkinMeshRenderer.renderTransparent(mDirect3D11.getDeviceContextPointer(), mpCamera, mLight);
		mSpriteRenderer.renderTransparent(mDirect3D11.getDeviceContextPointer(), mpCamera, mLight);
		mQuadRenderer.renderTransparent(mDirect3D11.getDeviceContextPointer(), mpCamera, mLight);
	}
}

void Renderer::renderUI()
{
	//UIの描画・カリングを無効化、UI用ビューポートの設定
	mDirect3D11.setViewport(1, &mUIPort);
	mDirect3D11.setCullNone();
	{
		//不透過オブジェクト描画
		mSpriteRenderer.renderUI(mDirect3D11.getDeviceContextPointer(), mUIMatrix);
		mQuadRenderer.renderUI(mDirect3D11.getDeviceContextPointer(), mUIMatrix);

		//透過オブジェクト描画
		mSpriteRenderer.renderTransparentUI(mDirect3D11.getDeviceContextPointer(), mUIMatrix);
		mQuadRenderer.renderTransparentUI(mDirect3D11.getDeviceContextPointer(), mUIMatrix);
	}
}

void Renderer::load(const OBJMeshID& id, const LPSTR & fileName)
{
	mOBJStaticMeshRenderer.addMesh(mDirect3D11.getDevicePointer(), id, fileName);
}

void Renderer::load(const FBXHierarchyID & id, const LPSTR & fileName)
{
	mFBXHierarchyMeshRenderer.addMesh(mDirect3D11.getDevicePointer(), id, fileName);
}

void Renderer::load(const FBXSkinID & id, const LPSTR & fileName)
{
	mFBXSkinMeshRenderer.addMesh(mDirect3D11.getDevicePointer(), id, fileName);
}

void Renderer::load(const TextureID & id, const LPCWSTR & fileName)
{
	mSpriteRenderer.addSprite(mDirect3D11.getDevicePointer(), id, fileName);
}

void Renderer::load(const ShaderTextureID & id, const LPCWSTR & fileName)
{
	mQuadRenderer.addQuad(mDirect3D11.getDevicePointer(), id, fileName);
}

void Renderer::render(const OBJStaticMeshRenderDesc * pDesc)
{
	mOBJStaticMeshRenderer.registerDesc(pDesc);
}

void Renderer::render(const FBXHierarchyMeshRenderDesc* pDesc)
{
	mFBXHierarchyMeshRenderer.registerDesc(pDesc);
}

void Renderer::render(const FBXSkinMeshRenderDesc * pDesc)
{
	mFBXSkinMeshRenderer.registerDesc(pDesc);
}

void Renderer::render(const TextRenderDesc & desc)
{
}

void Renderer::render(const SpriteRenderDesc * pDesc)
{
	mSpriteRenderer.registerDesc(pDesc);
}

void Renderer::render(const QuadRenderDesc * pDesc)
{
	mQuadRenderer.registerDesc(pDesc);
}

void Renderer::render(const UIImageRenderDesc * pDesc)
{
	mSpriteRenderer.registerUIData(pDesc);
}

void Renderer::render(const UIQuadRenderDesc * pDesc)
{
	mQuadRenderer.registerUIData(pDesc);
}

void Renderer::setRenderCamera(Camera* camera)
{
	mpCamera = camera;
	mDirect3D11.setViewport(1, &camera->Viewport);
}

void Renderer::setDirectionalLight(const DirectionalLightDesc & desc)
{
	mLight = desc;
}

void Renderer::clear()
{
	//各レンダリングデータのクリア
	mOBJStaticMeshRenderer.clear();
	mFBXHierarchyMeshRenderer.clear();
	mFBXSkinMeshRenderer.clear();
	mSpriteRenderer.clear();
	mQuadRenderer.clear();
	mSpriteRenderer.clearUI();
	mQuadRenderer.clearUI();

	//画面クリア
	mDirect3D11.clear();
}

void Renderer::present()
{
	mDirect3D11.present();
}

/****** End of File *****************************************************/
