//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Window.h
//!
//! @brief  ウィンドウクラスのヘッダファイル
//!
//! @date   
//!
//! @author 
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// 多重インクルード防止 ====================================================
#pragma once




// ヘッダファイルの読み込み ================================================
#include <Windows.h>




//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//! @brief ウィンドウクラス
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
class Window final
{

	// 定数
public:
	static const int WINDOW_WIDTH = 1280;		// ウィンドウ幅
	static const int WINDOW_HEIGHT = 780;		// ウィンドウ高さ


												// メンバ変数 ----------------------------------------------
private:
	HWND				m_handle;				// ウィンドウハンドル
	MSG					m_messageInfo;			// メッセージ情報
	static Window*		m_pWindow;              // 　


												// コンストラクタ ------------------------------------------
private:
	Window();



	// デストラクタ --------------------------------------------
public:
	~Window() = default;



	// 属性 ----------------------------------------------------
public:

	// Windowオブジェクトへのアドレスを取得する
	static Window* GetInstance()
	{
		if (m_pWindow == nullptr)
		{
			m_pWindow = new Window();
		}

		return m_pWindow;
	}


	// ウィンドウハンドルの取得
	HWND GetHandle()
	{
		return m_handle;
	}

	// 終了コードの取得
	int GetExitValue()
	{
		return m_messageInfo.wParam;
	}



	// 操作 ----------------------------------------------------
public:
	// メッセージの処理
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



	// 内部実装 ------------------------------------------------
private:
	// 初期化
	HRESULT Initialize(LPCWSTR title)
	{
		LPCWCHAR CLASS_NAME = L"GameWindowClass";
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

		int windowWidth = rect.right - rect.left;
		int windowHeight = rect.bottom - rect.top;


		// ウィンドウの作成
		m_handle = CreateWindow(
			CLASS_NAME,
			title,
			windowStyle,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			windowWidth,
			windowHeight,
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



	// クラス実装 ----------------------------------------------
public:
	// ファクトリメソッド
	static Window* Create(LPCWSTR title, int width, int height)
	{
		// ウインドウオブジェクトの生成
		Window* pWindow = new Window();

		if (!pWindow)
		{
			return nullptr;
		}


		// 初期化
		if (FAILED(pWindow->Initialize(title, width, height)))
		{
			delete pWindow;
			return nullptr;
		}


		// ウィンドウオブジェクトの生成に成功
		return pWindow;
	}

	// ウィンドウ・プロシージャ
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




};