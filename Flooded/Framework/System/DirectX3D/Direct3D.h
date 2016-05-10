//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Direct3D.h
//!
//! @brief  Direct3Dクラスのヘッダファイル
//!
//! @date   2014/11/10
//!
//! @author 高木 晋
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// 多重インクルード防止 ====================================================
#pragma once




// ヘッダファイルの読み込み ================================================
#include <Windows.h>

#include <d3d11.h>

#include "Framework\Utility\ComHelper.h"




// クラス定義 ==============================================================
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//! @brief Direct3Dクラス
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
class Direct3D final
{
	// メンバ変数 ----------------------------------------------
private:
	//HWND m_hWindow;   //!< ウィンドウハンドル

	// Direct3Dオブジェクト
	ComPtr<ID3D11Device>           m_pDevice = nullptr;   //!< デバイス
	ComPtr<ID3D11DeviceContext>	   m_pImmediateContext = nullptr;   //!< イミディエイトコンテキスト
	ComPtr<IDXGISwapChain>		   m_pSwapChain = nullptr;   //!< スワップチェーン

	// Direct3Dレンダリングオブジェクト
	ComPtr<ID3D11RenderTargetView> m_pRenderTargetView = nullptr;   //!< レンダーターゲットビュー
	ComPtr<ID3D11DepthStencilView> m_pDepthStencilView = nullptr;   //!< 深度ステンシルビュー

	// デバイスプロパティ
	UINT						   m_renderTargetWidth = 0;			//!< レンダーターゲットの幅
	UINT						   m_renderTargetHeight = 0;		//!< レンダーターゲットの高さ

	static Direct3D*			   m_pDirect3D;

	// コンストラクタ ------------------------------------------
private:
	Direct3D()
	{
	}



	// デストラクタ --------------------------------------------
public:
	// = default 空になる
	~Direct3D() = default;



	// 属性 ----------------------------------------------------
public:

	// DrirectX3Dオブジェクトへのアドレスを取得する
	static Direct3D* GetInstance()
	{
		if (m_pDirect3D == nullptr)
		{
			m_pDirect3D = new Direct3D();
		}

		return m_pDirect3D;
	}


	// デバイスの取得
	ID3D11Device* GetDevice()
	{
		return m_pDevice.Get();
	}

	// デバイスコンテキストの取得
	ID3D11DeviceContext* GetDeviceContext()
	{
		return m_pImmediateContext.Get();
	}

	// スワップチェーンの取得
	IDXGISwapChain* GetSwapChain()
	{
		return m_pSwapChain.Get();
	}

	// レンダーターゲットビューの取得
	ID3D11RenderTargetView* GetRenderTargetView()
	{
		return m_pRenderTargetView.Get();
	}

	// 深度ステンシルビューの取得
	ID3D11DepthStencilView* GetDepthStencilView()
	{
		return m_pDepthStencilView.Get();
	}



	// 操作 ----------------------------------------------------
public:
	// 表示モードの設定
	HRESULT SetFullscreenState(bool isFullscreen)
	{
		return m_pSwapChain->SetFullscreenState(isFullscreen, NULL);
	}



	// 内部実装 ------------------------------------------------
private:
	// デバイスリソースの作成
	void CreateDeviceResources()
	{

		// デバイス作成フラグの設定
		UINT creationFlags = 0;    // デバイス作成で使用するパラメーター

		creationFlags |= D3D11_CREATE_DEVICE_BGRA_SUPPORT;    // Direct3Dリソースとの相互運用性をDirect2Dで実現するために必要
#if defined(_DEBUG)
		creationFlags |= D3D11_CREATE_DEVICE_DEBUG;           // SDKレイヤーによるデバッグを有効化(Debug時のみ)
#endif


															  // サポートされるDirectXハードウェア機能レベルのセットの定義(順番に注意)											  // サポートされるDirectXハードウェア機能レベルのセットの定義(順番に注意)
		D3D_FEATURE_LEVEL featureLevels[] =
		{
			D3D_FEATURE_LEVEL_11_1,
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_10_0,
			D3D_FEATURE_LEVEL_9_3,
			D3D_FEATURE_LEVEL_9_2,
			D3D_FEATURE_LEVEL_9_1
		};

		D3D_FEATURE_LEVEL featureLevel;    //!< デバイスの機能レベル


										   // Direct3D11デバイスオブジェクトおよび対応するデバイスコンテキストの作成
		D3D11CreateDevice(
			nullptr,                     // [in]  既定のアダプターを使用するためnullptrを指定
			D3D_DRIVER_TYPE_HARDWARE,    // [in]  ハードウェアグラフィックスドライバーを使用
			nullptr,                     // [in]  D3D_DRIVER_TYPE_SOFTWAREでない限りnullptrを指定
			creationFlags,               // [in]  有効にするランタイムレイヤーの指定
			featureLevels,               // [in]  このアプリがサポートできる機能レベルの一覧
			ARRAYSIZE(featureLevels),    // [in]  上記リストの要素数
			D3D11_SDK_VERSION,           // [in]  SDKのバージョン(常にD3D11_SDK_VERSION)を指定
			&m_pDevice,                  // [out] 作成されたデバイス
			&featureLevel,               // [out] 作成されたデバイスの機能レベル(失敗した場合は0)
			&m_pImmediateContext         // [out] デバイスのイミディエイトコンテキスト
			);
	}
	

	// ウィンドウサイズに依存するリソースの作成
	void CreateWindowSizeDependentResources()
	{
		// レンダーターゲットのサイズの算出
		RECT clientArea;
		GetClientRect(Window::, &clientArea);

		m_renderTargetWidth = clientArea.right - clientArea.left;
		m_renderTargetHeight = clientArea.bottom - clientArea.top;


		// スワップチェーンの作成
		CreateSwapChain();

		// レンダーターゲットビューの作成
		CreateRenderTargetView();

		// 深度ステンシルビューの作成
		CreateDepthStencilView();


		// デバイスにレンダーターゲットおよび深度ステンシルビューをバインド
		BindRenderTarget();


		// ビューポートの設定
		SetViewPort();
	}

	// スワップチェーンの作成
	void CreateSwapChain()
	{
		// スワップチェインの設定を指定
		DXGI_SWAP_CHAIN_DESC swapChainDesc;
		ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

		swapChainDesc.BufferDesc.Width = m_renderTargetWidth;                // レンダーターゲットのサイズと一致させる
		swapChainDesc.BufferDesc.Height = m_renderTargetHeight;
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;         // 最も一般的なスワップチェーンのフォーマットを指定
		swapChainDesc.SampleDesc.Count = 1;                                  // マルチサンプリング不使用
		swapChainDesc.SampleDesc.Quality = 0;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferCount = 2;                                  // 遅延を最小限に抑えるためにダブルバッファを使用
		swapChainDesc.OutputWindow = m_hWindow;
		swapChainDesc.Windowed = TRUE;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		swapChainDesc.Flags = 0;


		// Direct3Dデバイスを作成する際に使用されたDXGIファクトリを取得してスワップチェーンを作成
		ComPtr<IDXGIDevice> dxgiDevice;
		m_pDevice.As(&dxgiDevice);

		ComPtr<IDXGIAdapter> dxgiAdapter;
		dxgiDevice->GetAdapter(&dxgiAdapter);

		ComPtr<IDXGIFactory> dxgiFactory;
		dxgiAdapter->GetParent(IID_PPV_ARGS(&dxgiFactory));

		dxgiFactory->CreateSwapChain(m_pDevice.Get(), &swapChainDesc, &m_pSwapChain);


		// フルスクリーンの不具合を直すためにバッファをリサイズ
		m_pSwapChain->ResizeBuffers(swapChainDesc.BufferCount, 0, 0, DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH);

	}

	// レンダーターゲットビューの作成
	void CreateRenderTargetView()
	{
		ComPtr<ID3D11Texture2D> pBackBuffer;
		m_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));

		m_pDevice->CreateRenderTargetView(pBackBuffer.Get(), nullptr, &m_pRenderTargetView);
	}

	// 深度ステンシルビューの作成
	void CreateDepthStencilView()
	{
		// スワップチェーンの設定を取得
		DXGI_SWAP_CHAIN_DESC swapChainDesc;
		m_pSwapChain->GetDesc(&swapChainDesc);


		// 深度ステンシルの設定の指定
		D3D11_TEXTURE2D_DESC depthStencilDesc;
		ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));

		depthStencilDesc.Width = m_renderTargetWidth;              // レンダーターゲットのサイズと一致させる
		depthStencilDesc.Height = m_renderTargetHeight;
		depthStencilDesc.MipLevels = 1;                                // ミップマップを作成しない
		depthStencilDesc.ArraySize = 1;                                // テクスチャーの枚数は1つ
		depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;    // フォーマット
		depthStencilDesc.SampleDesc = swapChainDesc.SampleDesc;         // スワップチェーンに一致させる
		depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;              // GPUによる読み書きアクセスを必要とするリソース
		depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;         // テクスチャーを深度ステンシルターゲットとしてバインド
		depthStencilDesc.CPUAccessFlags = 0;                                // CPUアクセスが不要。
		depthStencilDesc.MiscFlags = 0;                                // その他のフラグも設定しない		


																	   // 深度ステンシルの作成
		ComPtr<ID3D11Texture2D> depthStencil;
		m_pDevice->CreateTexture2D(&depthStencilDesc, nullptr, &depthStencil);


		// 深度ステンシルビューの設定の指定
		D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
		ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));

		depthStencilViewDesc.Format = depthStencilDesc.Format;          // 深度ステンシルに一致させる
		depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;    // マルチサンプリング不使用


		// 深度ステンシルビューの作成
		m_pDevice->CreateDepthStencilView(depthStencil.Get(), &depthStencilViewDesc, &m_pDepthStencilView);
	}

	// デバイスにレンダーターゲットおよび深度ステンシルビューをバインド
	void BindRenderTarget()
	{
		ID3D11RenderTargetView* targets[] = { m_pRenderTargetView.Get() };
		m_pImmediateContext->OMSetRenderTargets(1, targets, m_pDepthStencilView.Get());

	}

	// ビューポートの設定
	void SetViewPort()
	{
		// レンダリングビューポートをウィンドウ全体をターゲットにするように設定
		D3D11_VIEWPORT viewport;

		viewport.TopLeftX = 0.0f;
		viewport.TopLeftY = 0.0f;
		viewport.Width = static_cast<FLOAT>(m_renderTargetWidth);
		viewport.Height = static_cast<FLOAT>(m_renderTargetHeight);
		viewport.MinDepth = D3D11_MIN_DEPTH;
		viewport.MaxDepth = D3D11_MAX_DEPTH;

		m_pImmediateContext->RSSetViewports(1, &viewport);
	}

	// 初期化
	void Initialize(HWND hWindow)
	{
		m_hWindow = Window::GetInstance()->GetHandle();


		// リソースの作成
		CreateDeviceResources();
		CreateWindowSizeDependentResources();


		
	}



	// クラス実装 ----------------------------------------------
public:
	// ファクトリメソッド
	static Direct3D* Create(HWND hWindow)
	{
		// Direct3Dオブジェクトの生成
		Direct3D* pDirect3D = new Direct3D();

		if (!pDirect3D)
		{
			return nullptr;
		}


		// 初期化
		if (FAILED(pDirect3D->Initialize(hWindow)))
		{
			delete pDirect3D;
			return nullptr;
		}


		// Direct3Dオブジェクトの生成に成功
		return pDirect3D;
	}

};