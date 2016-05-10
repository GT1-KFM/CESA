// test 16/05/10
// part2
// 多重インクルード防止 ====================================================
#pragma once

// ヘッダファイルの読み込み ================================================
#include <Windows.h>

// クラス定義 ==============================================================
	// ウィンドウクラス
	class Window final
	{
		// メンバ変数 ----------------------------------------------
		private:
			HWND m_handle;         // ウィンドウハンドル
			MSG  m_messageInfo;    // メッセージ情報

		// コンストラクタ ------------------------------------------
		private:
			Window();

		// デストラクタ --------------------------------------------
		public:
			~Window() = default;

		// 属性 ----------------------------------------------------
		public:
			// ウィンドウハンドルの取得
			HWND GetHandle() const;

			// 終了コードの取得
			int GetExitValue() const;

		// 操作 ----------------------------------------------------
		public:
			// メッセージの処理
			bool HandleMessage();

		// 内部実装 ------------------------------------------------
		private:
			// 初期化
			HRESULT Initialize(LPCWSTR title, int width, int height);

		// クラス実装 ----------------------------------------------
		public:
			// ファクトリメソッド
			static Window* Create(LPCWSTR title, int width, int height);
	
			// ウィンドウ・プロシージャ
			static LRESULT CALLBACK Procedure(HWND hWindow, UINT uMessage, WPARAM wParam, LPARAM lParam);
	};