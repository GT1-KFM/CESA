//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Direct3D.cpp
//!
//! @brief  Direct3Dクラスのソースファイル
//!
//! @date   2014/10/10
//!
//! @author 高木 晋
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// ヘッダファイルの読み込み ================================================
#include "Direct3D.h"




// ライブラリの追加 ========================================================
#pragma comment(lib, "d3d11.lib")    // Direct3D11用ライブラリ




// メンバ関数の定義 ========================================================
namespace Framework
{
	/*
	//------------------------------------------------------------------
	//! @brief デフォルトコンストラクタ
	//!
	//! @param なし
	//------------------------------------------------------------------
	Direct3D::Direct3D()
		: m_hWindow(nullptr)
		, m_pDevice(nullptr)
		, m_pImmediateContext(nullptr)
		, m_pSwapChain(nullptr)
		, m_pRenderTargetView(nullptr)
		, m_pDepthStencilView(nullptr)
		, m_renderTargetWidth(0)
		, m_renderTargetHeight(0)
	{
	}



	//------------------------------------------------------------------
	//! @brief デバイスの取得
	//!
	//! @param なし
	//!
	//! @return デバイス
	//------------------------------------------------------------------
	ID3D11Device* Direct3D::GetDevice() const
	{
		return m_pDevice.Get();
	}



	//------------------------------------------------------------------
	//! @brief デバイスコンテキストの取得
	//!
	//! @param なし
	//!
	//! @return デバイスコンテキスト(イミディエイトコンテキスト)
	//------------------------------------------------------------------
	ID3D11DeviceContext* Direct3D::GetDeviceContext() const
	{
		return m_pImmediateContext.Get();
	}



	//------------------------------------------------------------------
	//! @brief スワップチェーンの取得
	//!
	//! @param なし
	//!
	//! @return スワップチェーン
	//------------------------------------------------------------------
	IDXGISwapChain* Direct3D::GetSwapChain() const
	{
		return m_pSwapChain.Get();
	}



	//------------------------------------------------------------------
	//! @brief レンダーターゲットビューの取得
	//!
	//! @param なし
	//!
	//! @return レンダーターゲットビュー
	//------------------------------------------------------------------
	ID3D11RenderTargetView* Direct3D::GetRenderTargetView() const
	{
		return m_pRenderTargetView.Get();
	}



	//------------------------------------------------------------------
	//! @brief 深度ステンシルビューの取得
	//!
	//! @param なし
	//!
	//! @return 深度ステンシルビュー
	//------------------------------------------------------------------
	ID3D11DepthStencilView* Direct3D::GetDepthStencilView() const
	{
		return m_pDepthStencilView.Get();
	}



	//------------------------------------------------------------------
	//! @brief 表示モードの設定
	//!
	//! @param[in] isFullscreen フルスクリーンにするかどうか
	//!
	//! @return なし
	//------------------------------------------------------------------
	HRESULT Direct3D::SetFullscreenState(bool isFullscreen)
	{
		return m_pSwapChain->SetFullscreenState(isFullscreen, nullptr);
	}



	//------------------------------------------------------------------
	//! @brief デバイスリソースの作成
	//!
	//! @param なし
	//!
	//! @return なし
	//!
	//! @exception COMメソッドの実行結果がエラーの場合、COM例外オブジェクトを送出
	//------------------------------------------------------------------
	void Direct3D::CreateDeviceResources()
	{
		// デバイス作成フラグの設定
		UINT creationFlags = 0;    // デバイス作成で使用するパラメーター

		creationFlags |= D3D11_CREATE_DEVICE_BGRA_SUPPORT;    // Direct3Dリソースとの相互運用性をDirect2Dで実現するために必要
#if defined(_DEBUG)
		creationFlags |= D3D11_CREATE_DEVICE_DEBUG;           // SDKレイヤーによるデバッグを有効化(Debug時のみ)
#endif


		// サポートされるDirectXハードウェア機能レベルのセットの定義(順番に注意)
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
		THROW_IF_FAILED(
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
			)
		);
	}



	//------------------------------------------------------------------
	//! @brief ウィンドウサイズに依存するリソースの作成
	//!
	//! @param なし
	//!
	//! @return なし
	//------------------------------------------------------------------
	void Direct3D::CreateWindowSizeDependentResources()
	{
		// レンダーターゲットのサイズの算出
		RECT clientArea;
		GetClientRect(m_hWindow, &clientArea);

		m_renderTargetWidth  = clientArea.right  - clientArea.left;
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


	
	//------------------------------------------------------------------
	//! @brief スワップチェーンの作成
	//!
	//! @param なし
	//!
	//! @return なし
	//!
	//! @exception COMメソッドの実行結果がエラーの場合、COM例外オブジェクトを送出
	//------------------------------------------------------------------
	void Direct3D::CreateSwapChain()
	{
		// スワップチェインの設定を指定
		DXGI_SWAP_CHAIN_DESC swapChainDesc;
		ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

		swapChainDesc.BufferDesc.Width   = m_renderTargetWidth;                // レンダーターゲットのサイズと一致させる
		swapChainDesc.BufferDesc.Height  = m_renderTargetHeight;
		swapChainDesc.BufferDesc.Format  = DXGI_FORMAT_B8G8R8A8_UNORM;         // 最も一般的なスワップチェーンのフォーマットを指定
		swapChainDesc.SampleDesc.Count   = 1;                                  // マルチサンプリング不使用
		swapChainDesc.SampleDesc.Quality = 0;
		swapChainDesc.BufferUsage        = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferCount        = 2;                                  // 遅延を最小限に抑えるためにダブルバッファを使用
		swapChainDesc.OutputWindow       = m_hWindow;
		swapChainDesc.Windowed           = TRUE;
		swapChainDesc.SwapEffect         = DXGI_SWAP_EFFECT_DISCARD;
		swapChainDesc.Flags              = 0;


		// Direct3Dデバイスを作成する際に使用されたDXGIファクトリを取得してスワップチェーンを作成
		ComPtr<IDXGIDevice> dxgiDevice;
		THROW_IF_FAILED(
			m_pDevice.As(&dxgiDevice)
		);

		ComPtr<IDXGIAdapter> dxgiAdapter;
		THROW_IF_FAILED(
			dxgiDevice->GetAdapter(&dxgiAdapter)
		);

		ComPtr<IDXGIFactory> dxgiFactory;
		THROW_IF_FAILED(
			dxgiAdapter->GetParent(IID_PPV_ARGS(&dxgiFactory))
		);

		THROW_IF_FAILED(
			dxgiFactory->CreateSwapChain(m_pDevice.Get(), &swapChainDesc, &m_pSwapChain)
		);


		// フルスクリーンの不具合を直すためにバッファをリサイズ
		m_pSwapChain->ResizeBuffers(swapChainDesc.BufferCount, 0, 0, DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH);
	}



	//------------------------------------------------------------------
	//! @brief レンダーターゲットビューの作成
	//!
	//! @param なし
	//!
	//! @return なし
	//!
	//! @exception COMメソッドの実行結果がエラーの場合、COM例外オブジェクトを送出
	//------------------------------------------------------------------
	void Direct3D::CreateRenderTargetView()
	{
		ComPtr<ID3D11Texture2D> pBackBuffer;
		THROW_IF_FAILED(
			m_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer))
		);

		THROW_IF_FAILED(
			m_pDevice->CreateRenderTargetView(pBackBuffer.Get(), nullptr, &m_pRenderTargetView)
		);
	}



	//------------------------------------------------------------------
	//! @brief 深度ステンシルビューの作成
	//!
	//! @param なし
	//!
	//! @return なし
	//!
	//! @exception COMメソッドの実行結果がエラーの場合、COM例外オブジェクトを送出
	//------------------------------------------------------------------
	void Direct3D::CreateDepthStencilView()
	{
		// スワップチェーンの設定を取得
		DXGI_SWAP_CHAIN_DESC swapChainDesc;
		m_pSwapChain->GetDesc(&swapChainDesc);


		// 深度ステンシルの設定の指定
		D3D11_TEXTURE2D_DESC depthStencilDesc;
		ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));

		depthStencilDesc.Width          = m_renderTargetWidth;              // レンダーターゲットのサイズと一致させる
		depthStencilDesc.Height         = m_renderTargetHeight; 
		depthStencilDesc.MipLevels      = 1;                                // ミップマップを作成しない
		depthStencilDesc.ArraySize      = 1;                                // テクスチャーの枚数は1つ
		depthStencilDesc.Format         = DXGI_FORMAT_D24_UNORM_S8_UINT;    // フォーマット
		depthStencilDesc.SampleDesc     = swapChainDesc.SampleDesc;         // スワップチェーンに一致させる
		depthStencilDesc.Usage          = D3D11_USAGE_DEFAULT;              // GPUによる読み書きアクセスを必要とするリソース
		depthStencilDesc.BindFlags      = D3D11_BIND_DEPTH_STENCIL;         // テクスチャーを深度ステンシルターゲットとしてバインド
		depthStencilDesc.CPUAccessFlags = 0;                                // CPUアクセスが不要。
		depthStencilDesc.MiscFlags      = 0;                                // その他のフラグも設定しない		


		// 深度ステンシルの作成
		ComPtr<ID3D11Texture2D> depthStencil;
		THROW_IF_FAILED(
			m_pDevice->CreateTexture2D(&depthStencilDesc, nullptr, &depthStencil)
		);


		// 深度ステンシルビューの設定の指定
		D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
		ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));

		depthStencilViewDesc.Format        = depthStencilDesc.Format;          // 深度ステンシルに一致させる
		depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;    // マルチサンプリング不使用


		// 深度ステンシルビューの作成
		THROW_IF_FAILED(
			m_pDevice->CreateDepthStencilView(depthStencil.Get(), &depthStencilViewDesc, &m_pDepthStencilView)
		);
	}



	//------------------------------------------------------------------
	//! @brief デバイスにレンダーターゲットおよび深度ステンシルビューをバインド
	//!
	//! @param なし
	//!
	//! @return なし
	//------------------------------------------------------------------
	void Direct3D::BindRenderTarget()
	{
		ID3D11RenderTargetView* targets[] = { m_pRenderTargetView.Get() };
		m_pImmediateContext->OMSetRenderTargets(1, targets, m_pDepthStencilView.Get());
	}



	//------------------------------------------------------------------
	//! @brief ビューポートの設定
	//!
	//! @param なし
	//!
	//! @return なし
	//------------------------------------------------------------------
	void Direct3D::SetViewPort()
	{
		// レンダリングビューポートをウィンドウ全体をターゲットにするように設定
		D3D11_VIEWPORT viewport;

		viewport.TopLeftX = 0.0f;
		viewport.TopLeftY = 0.0f;
		viewport.Width    = static_cast<FLOAT>(m_renderTargetWidth);
		viewport.Height   = static_cast<FLOAT>(m_renderTargetHeight);
		viewport.MinDepth = D3D11_MIN_DEPTH;
		viewport.MaxDepth = D3D11_MAX_DEPTH;

		m_pImmediateContext->RSSetViewports(1, &viewport);
	}



	//------------------------------------------------------------------
	//! @brief 初期化
	//!
	//! @param[in] hWindow ウィンドウハンドル
	//!
	//! @retval S_OK         初期化に成功
	//! @retval エラーコード 初期化に失敗
	//------------------------------------------------------------------
	HRESULT Direct3D::Initialize(HWND hWindow)
	{
		m_hWindow = hWindow;


		// リソースの作成
		try {
			CreateDeviceResources();
			CreateWindowSizeDependentResources();
		}
		catch (ComException& exception)
		{
			exception.PopUpMessageBox();
			return exception.GetErrorCode();
		}


		// 初期化に成功
		return S_OK;
	}
}




// 静的メンバ関数の定義 ======================================================
namespace Framework
{
	//------------------------------------------------------------------
	//! @brief Direct3Dオブジェクトの生成
	//!
	//! @param[in] hWindow ウィンドウハンドル
	//!
	//! @retval Direct3Dオブジェクト 成功
	//! @retval nullptr              失敗
	//------------------------------------------------------------------
	Direct3D* Direct3D::Create(HWND hWindow)
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
	*/
}