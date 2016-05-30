////////////////////////////////////////////////////////////////////////////
//! @file   WinMain.cpp
//!
//! @brief  WinMainのソースファイル
//!
//! @date   2016/5/18
//!
//! @author 近藤　優和
////////////////////////////////////////////////////////////////////////////

// インクルードの読み込み
#include <windows.h>
#include "ScreenMode.h"
#include <memory>
#include "GameBase.h"
#include "GameMain.h"
#include "..\Utility\MemoryLeakDetector.h"



// 名前空間の使用宣言
using namespace std;


//----------------------------------------------------------------------
//! @brief プログラムのエントリーポイント
//!
//! @param[in] hInstance     現在のインスタンスのハンドル
//! @param[in] hPrevInstance 以前のインスタンスのハンドル(常にnullptr)
//! @param[in] lpCmdLine     コマンドライン
//! @param[in] nCmdShow      ウィンドウの表示状態
//!
//! @retval 終了コード 正常終了
//! @retval 0          異常終了
//----------------------------------------------------------------------
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	// 未使用引数の警告対策
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(nCmdShow);


#if defined(_DEBUG)
	// メモリーリーク検出機構のセットアップ
	SetUpMemoryLeakDetector();
#endif

	// スクリーンモードの設定
	ScreenMode screenMode = ScreenMode::WINDOWED;

	// フルスクリーンの可否
	if (MessageBox(nullptr, L"フルスクリーンモードで起動しますか？", L"画面設定", MB_OKCANCEL) == IDOK)
	{
		screenMode = ScreenMode::FULLSCREEN;
	}

	// ゲームの作成
	unique_ptr<GameBase> game = make_unique<GameMain>();

	// ゲームの実行
	return game->Run(screenMode);

}