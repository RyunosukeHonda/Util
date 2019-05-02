#include "Direct3D11.h"
#include "Screen.h"

#include "Collision.h"

//
//
//
Direct3D11::Direct3D11(const HWND& wnd)
{
	ZeroMemory(this, sizeof(Direct3D11));
	init(wnd);
}

//
//
//
Direct3D11::~Direct3D11()
{
	SAFE_RELEASE(mpSwapChain);
	SAFE_RELEASE(mpRenderTargetView);
	SAFE_RELEASE(mpDepthStencilView);
	SAFE_RELEASE(mpDepthStencil);
	SAFE_RELEASE(mpDeviceContext);
	SAFE_RELEASE(mpDevice);
}
//
//
//
HRESULT Direct3D11::init(const HWND& wnd)
{
	// デバイスとスワップチェーンの作成
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = Screen::WINDOW_WIDTH;
	sd.BufferDesc.Height = Screen::WINDOW_HEIGHT;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = wnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;

	D3D_FEATURE_LEVEL pFeatureLevels = D3D_FEATURE_LEVEL_11_0;
	D3D_FEATURE_LEVEL* pFeatureLevel = NULL;

	if (FAILED(D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL,
		0, &pFeatureLevels, 1, D3D11_SDK_VERSION, &sd, &mpSwapChain, &mpDevice,
		pFeatureLevel, &mpDeviceContext)))
	{
		return FALSE;
	}

	//レンダーターゲットビューの作成
	ID3D11Texture2D *pBackBuffer;
	mpSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	mpDevice->CreateRenderTargetView(pBackBuffer, NULL, &mpRenderTargetView);
	SAFE_RELEASE(pBackBuffer);

	//深度ステンシルビューの作成
	D3D11_TEXTURE2D_DESC descDepth;
	descDepth.Width = Screen::WINDOW_WIDTH;
	descDepth.Height = Screen::WINDOW_HEIGHT;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D32_FLOAT;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;
	mpDevice->CreateTexture2D(&descDepth, NULL, &mpDepthStencil);
	mpDevice->CreateDepthStencilView(mpDepthStencil, NULL, &mpDepthStencilView);

	//レンダーターゲットビューと深度ステンシルビューをパイプラインにバインド
	mpDeviceContext->OMSetRenderTargets(1, &mpRenderTargetView, mpDepthStencilView);

	////震度ステンシルステートを作成
	D3D11_DEPTH_STENCIL_DESC dc;
	ZeroMemory(&dc, sizeof(dc));
	dc.DepthEnable = true;
	dc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dc.DepthFunc = D3D11_COMPARISON_LESS;
	dc.StencilEnable = false;
	if (FAILED(mpDevice->CreateDepthStencilState(&dc, &mpDepthStencilState)))
	{
		return E_FAIL;
	}
	//深度ステンシルステートを適用
	mpDeviceContext->OMSetDepthStencilState(mpDepthStencilState, 0);

	///ラスタライズ設定
	///カリングトリック用に前面背面両方のカリングステートを、
	///UI描画用にカリング無効化ステートを作成
	D3D11_RASTERIZER_DESC rdc;
	ZeroMemory(&rdc, sizeof(rdc));
	rdc.CullMode = D3D11_CULL_FRONT;
	rdc.FillMode = D3D11_FILL_SOLID;
	rdc.FrontCounterClockwise = TRUE;
	mpDevice->CreateRasterizerState(&rdc, &mpRasterizerStateFront);
	rdc.CullMode = D3D11_CULL_BACK;
	mpDevice->CreateRasterizerState(&rdc, &mpRasterizerStateBack);
	rdc.CullMode = D3D11_CULL_NONE;
	mpDevice->CreateRasterizerState(&rdc, &mpRasterizerStateNone);
	//初期設定は背面カリング
	mpDeviceContext->RSSetState(mpRasterizerStateBack);

	//アルファブレンド用ブレンドステート作成
	D3D11_BLEND_DESC bd;
	ZeroMemory(&bd, sizeof(D3D11_BLEND_DESC));
	bd.IndependentBlendEnable = false;
	bd.AlphaToCoverageEnable = false;
	bd.RenderTarget[0].BlendEnable = true;
	bd.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	bd.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	if (FAILED(mpDevice->CreateBlendState(&bd, &mpBlendState)))
	{
		return E_FAIL;
	}
	UINT mask = 0xffffffff;
	mpDeviceContext->OMSetBlendState(mpBlendState, NULL, mask);

	///衝突判定でコンピュートシェーダーを使用するため
	///デバイス情報を送り初期化しておく
	Collision::instance().init(mpDevice, mpDeviceContext);

	return S_OK;
}
//
//
//
void Direct3D11::clear()
{
	//画面クリア（実際は単色で画面を塗りつぶす処理）
	float ClearColor[4] = { 0,0,0,0 };// クリア色作成　RGBAの順
	mpDeviceContext->ClearRenderTargetView(mpRenderTargetView, ClearColor);//画面クリア
	mpDeviceContext->ClearDepthStencilView(mpDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);//深度バッファクリア
}
//
//
//
HRESULT Direct3D11::present()
{
	mpSwapChain->Present(0, 0);//画面更新（バックバッファをフロントバッファに）
	return S_OK;
}

void Direct3D11::setCullFront()
{
	mpDeviceContext->RSSetState(mpRasterizerStateFront);
}

void Direct3D11::setCullBack()
{
	mpDeviceContext->RSSetState(mpRasterizerStateBack);
}

void Direct3D11::setCullNone()
{
	mpDeviceContext->RSSetState(mpRasterizerStateNone);
}

ID3D11Device * Direct3D11::getDevicePointer()
{
	return mpDevice;
}

ID3D11DeviceContext * Direct3D11::getDeviceContextPointer()
{
	return mpDeviceContext;
}

void Direct3D11::setViewport(const int viewportNum, const D3D11_VIEWPORT * viewport)
{
	mpDeviceContext->RSSetViewports(viewportNum, viewport);
}

/****** End of File *****************************************************/