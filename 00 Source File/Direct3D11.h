/**
* @file Direct3D11.h
* @brief Direct3D11描画機能管理クラス定義ファイル
* @author Ryunosuke Honda.
*/
#pragma once

#include "Base.h"
#include <d3d11.h>
#include <d3dx10.h>
#include <d3dx11.h>
#include <d3dCompiler.h>

/**
*	Direct3D11描画機能管理クラス
*/
class Direct3D11 : public CElement
{
public:
	/**
	* @fn
	* コンストラクタ
	* @param (wnd) ウィンドウハンドル
	*/
	Direct3D11(const HWND& wnd);

	/**
	* @fn
	* デストラクタ
	*/
	~Direct3D11();

	/**
	* @fn
	* ビューポート設定
	* @param (viewportNum) ビューポート番号
	* @param (viewport) ビューポート記述子
	*/
	void setViewport(const int viewportNum, const D3D11_VIEWPORT* viewport);
	
	/**
	* @fn
	* 画面クリア
	*/
	void clear();

	/**
	* @fn
	* 画面更新（バックバッファをフロントバッファに）
	*/
	HRESULT present();

	/**
	* @fn
	* 前面カリング設定を適用
	*/
	void setCullFront();

	/**
	* @fn
	* 背面カリング設定を適用
	*/
	void setCullBack();

	/**
	* @fn
	* カリングなし設定を適用
	* @brief
	* UIをカリングすると向きによっては見えなくなってしまうので
	* UI描画時だけカリングを切る
	*/
	void setCullNone();

	/**
	* @fn
	* デバイスポインタの取得
	*/
	ID3D11Device* getDevicePointer();

	/**
	* @fn
	* デバイスコンテキストポインタの取得
	*/
	ID3D11DeviceContext* getDeviceContextPointer();

private:
	/**
	* @fn
	* 初期化・一度行われれば十分なため生成時に行う
	*/
	HRESULT init(const HWND& wnd);

private:
	//!DirectXデバイス
	ID3D11Device* mpDevice;
	//!DirectXデバイスコンテキスト
	ID3D11DeviceContext* mpDeviceContext;
	//!スワップチェイン
	IDXGISwapChain* mpSwapChain;
	//!レンダーターゲット
	ID3D11RenderTargetView* mpRenderTargetView;
	//!デプス
	ID3D11DepthStencilView* mpDepthStencilView;
	//!デプスステンシル
	ID3D11Texture2D* mpDepthStencil;
	//!前面カリングステート
	ID3D11RasterizerState* mpRasterizerStateFront;
	//!背面カリングステート
	ID3D11RasterizerState* mpRasterizerStateBack;
	//!カリング無効化ステート
	ID3D11RasterizerState* mpRasterizerStateNone;
	//!ブレンドステート
	ID3D11BlendState* mpBlendState;
	//!デプスステンシルステート
	ID3D11DepthStencilState* mpDepthStencilState;
};

/****** End of File *****************************************************/