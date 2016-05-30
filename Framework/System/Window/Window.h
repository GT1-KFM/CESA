///////////////////////////////////////////////////////////////////////////////////
//! @file   Window.h
//!
//! @brief  ウィンドウクラスのヘッダファイル
//!
//! @date   2016/5/18
//!
//! @author 近藤優和
/////////////////////////////////////////////////////////////////////////////////

// 多重インクルード防止 
#pragma once




// ヘッダファイルの読み込み
#include <Windows.h>




// ---------------------------------------------------------------------------
// Windowクラス
// ---------------------------------------------------------------------------
class Window 
{

	// 静的メンバ変数 --------------------------------------------------------
public:
	static const int WINDOW_WIDTH  = 1280;		// ウィンドウ幅
	static const int WINDOW_HEIGHT = 720;		// ウィンドウ高さ
	static Window*		m_pWindow;              // ウィンドウのアドレス

	


	// メンバ変数 -------------------------------------------------------------
private:
	HWND				m_handle;				// ウィンドウハンドル
	MSG					m_messageInfo;			// メッセージ情報
	int					m_screenWidth;			// ウィンドウ幅
	int					m_screenHeight;			// ウィンドウ高さ

	// コンストラクタ ---------------------------------------------------------
private:
	Window() = default;



	// デストラクタ -----------------------------------------------------------
public:
	~Window() = default;



	// 静的メンバ関数 ---------------------------------------------------------
public:


	// ------------------------------------------------------------------------
	//! @brief      Windowオブジェクトへのアドレスを取得する
	//!
	//! @return     pWindow
	// ------------------------------------------------------------------------
	static Window* GetInstance()
	{
		// Windowを生成する
		if (m_pWindow == nullptr)
		{
			m_pWindow = Window::Create();
		}

		return m_pWindow;
	}




	
private:

	// ------------------------------------------------------------------------
	//! @brief      ウィンドウオブジェクトの生成
	//!
	//! @return     pWindow	生成に成功
	//! @return		nullptr	生成に失敗
	// ------------------------------------------------------------------------
	static Window* Create()
	{
		// ウインドウオブジェクトの生成
		Window* pWindow = new Window();

		if (!pWindow)
		{
			return nullptr;
		}


		// 初期化
		if (FAILED(pWindow->Initialize()))
		{
			delete pWindow;
			return nullptr;
		}


		// ウィンドウオブジェクトの生成に成功
		return pWindow;
	}


	// ------------------------------------------------------------------------
	//! @brief      ウィンドウプロシージャ
	//!
	//! @param[in]	hWindow	 ウィンドウハンドル
	//! @param[in]	uMessage メッセージの指定
	//! @param[in]	wParam	 メッセージの一番目のパラメータ
	//! @param[in]	lParam	 メッセージの二番目のパラメータ
	//!
	//! @return     0		終了要求
	//! @return     LRESULT	windowsメッセージの結果
	// ------------------------------------------------------------------------
	static LRESULT CALLBACK Procedure(HWND hWindow, UINT uMessage, WPARAM wParam, LPARAM lParam)
	{
		// メッセージの処理
		switch (uMessage)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

		case WM_KEYDOWN:
			if (wParam == VK_ESCAPE)
			{
				PostQuitMessage(0);
				return 0;
			}
			break;
		}

		// 自分で処理しないメッセージはWindowsに任せる
		return DefWindowProc(hWindow, uMessage, wParam, lParam);
	}


	// メンバ関数 -------------------------------------------------------------
public:

	// ------------------------------------------------------------------------
	//! @brief      ウィンドウハンドルの取得
	//!
	//! @return     handle(HWND)
	// ------------------------------------------------------------------------
	HWND GetHandle() const
	{
		return m_handle;
	}




	// ------------------------------------------------------------------------
	//! @brief     終了コードの取得 
	//!
	//! @return     wPaaram(int)
	// ------------------------------------------------------------------------
	int GetExitValue() const
	{
		return m_messageInfo.wParam;
	}




	// ------------------------------------------------------------------------
	//! @brief    ゲーム画面の幅を取得
	//!
	//! @return     wPaaram(int)
	// ------------------------------------------------------------------------
	int GetScreenWidth()
	{
		return m_screenWidth;
	}




	// ------------------------------------------------------------------------
	//! @brief     ゲーム画面の高さを取得 
	//!
	//! @return     wPaaram(int)
	// ------------------------------------------------------------------------
	int GetScreenHeight()
	{
		return m_screenHeight;
	}




public:

	// ------------------------------------------------------------------------
	//! @brief      メッセージの処理
	//!
	//! @return     false	ウィンドウの終了
	//! @return		true	ウィンドウの続行
	// ------------------------------------------------------------------------
	bool HandleMessage()
	{
		// ポスト済みメッセージの処理
		while (PeekMessage(&m_messageInfo, NULL, 0, 0, PM_REMOVE))
		{
			// WM_QUITメッセージの処理
			if (m_messageInfo.message == WM_QUIT)
			{
				return false;
			}

			// WM_QUIT以外のメッセージの処理
			TranslateMessage(&m_messageInfo);
			DispatchMessage(&m_messageInfo);
		}

		return true;
	}




private:

	// ------------------------------------------------------------------------
	//! @brief      初期化
	//!
	//! @return     E_FAIL	初期化失敗
	//! @return		S_OK    初期化成功
	// ------------------------------------------------------------------------
	HRESULT Initialize()
	{
		// クラスネーム
		LPCWSTR CLASS_NAME = L"GameWindowClass";
		// タイトルネーム
		LPCWSTR TITLE_NAME = L"Picker";
		// モジュールハンドルを得る
		HINSTANCE hInstance = GetModuleHandle(nullptr);


		// ウィンドウ・クラスを登録
		WNDCLASSEX windowClass;
		ZeroMemory(&windowClass, sizeof(windowClass));

		windowClass.cbSize = sizeof(WNDCLASSEX);
		windowClass.style = CS_HREDRAW | CS_VREDRAW;
		windowClass.lpfnWndProc = Window::Procedure;
		windowClass.cbClsExtra = 0;
		windowClass.cbWndExtra = 0;
		windowClass.hInstance = hInstance;
		windowClass.hIcon = LoadIcon(hInstance, L"ICON");
		windowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
		windowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		windowClass.lpszMenuName = nullptr;
		windowClass.lpszClassName = CLASS_NAME;
		windowClass.hIconSm = LoadIcon(hInstance, L"ICON");

		if (!RegisterClassEx(&windowClass))
		{
			// 初期化に失敗
			return E_FAIL;
		}


		// ウィンドウスタイルの設定
		DWORD windowStyle = WS_OVERLAPPEDWINDOW    // 基本スタイル(オーバーラップウィンドウ)
			& ~WS_MAXIMIZEBOX        // 最大化ボタンの無効化
			& ~WS_THICKFRAME;        // ウィンドウのサイズ変更の無効化


		// ウィンドウサイズの算出
		RECT rect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
		AdjustWindowRect(&rect, windowStyle, FALSE);

		m_screenWidth = rect.right - rect.left;
		m_screenHeight = rect.bottom - rect.top;


		// ウィンドウの作成
		m_handle = CreateWindow(
			CLASS_NAME,
			TITLE_NAME,
			windowStyle,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			m_screenWidth,
			m_screenHeight,
			nullptr,
			nullptr,
			windowClass.hInstance,
			NULL
			);

		if (!m_handle)
		{
			// 初期化に失敗
			return E_FAIL;
		}


		// ウィンドウの表示
		ShowWindow(m_handle, SW_SHOWNORMAL);


		// 初期化に成功
		return S_OK;
	}





};