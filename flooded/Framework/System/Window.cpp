// ヘッダファイルの読み込み ================================================
#include "Window.h"

// 名前空間の使用宣言 ======================================================
using namespace std;

	// @brief デフォルトコンストラクタ
	// @param なし
	Window::Window()
		: m_handle(nullptr)
		, m_messageInfo()
	{
		ZeroMemory(&m_messageInfo, sizeof(m_messageInfo));
	}

	// @brief ウィンドウハンドルの取得
	// @param なし
	// @return ウィンドウハンドル
	HWND Window::GetHandle() const
	{
		return m_handle;
	}

	// @brief 終了コードの取得
	// @param なし
	// @return 終了コード
	int Window::GetExitValue() const
	{
		return m_messageInfo.wParam;
	}

	// @brief メッセージの処理
	// @param なし
	// @retval true  メッセージが無い or WM_QUIT以外のメッセージを処理した場合
	// @retval false WM_QUITメッセージを受信した場合
	bool Window::HandleMessage()
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

	// @brief 初期化
	// @param[in] title  ウィンドウのタイトル
	// @param[in] width  クライアント領域の幅
	// @param[in] height クライアント領域の高さ
	// @retval S_OK   初期化に成功
	// @retval E_FAIL 初期化に失敗
	HRESULT Window::Initialize(LPCWSTR title, int width, int height)
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
		RECT rect = { 0, 0, width, height };
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


	// @briefウィンドウオブジェクトの生成
	// @param[in] title  ウィンドウのタイトル
	// @param[in] width  クライアント領域の幅
	// @param[in] height クライアント領域の高さ
	// @retval ウィンドウオブジェクト 成功
	// @retval nullptr                失敗
	Window* Window::Create(LPCWSTR title, int width, int height)
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

	// @brief ウィンドウ・プロシージャ
	// @param[in] hWindow  ウィンドウハンドル
	// @param[in] uMessage メッセージの識別子
	// @param[in] wParam   メッセージの1番目のパラメータ
	// @param[in] lParam   メッセージの2番目のパラメータ
	// @return メッセージ処理の結果(送信されたメッセージによって異なる)
	LRESULT CALLBACK Window::Procedure(HWND hWindow, UINT uMessage, WPARAM wParam, LPARAM lParam)
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