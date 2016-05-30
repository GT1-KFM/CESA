/////////////////////////////////////////////////////////////////////////////////
//! @file   GameBase.cpp
//!
//! @brief  ゲームの基本クラスのソースファイル
//!
//! @date   2016/5/18
//!
//! @author 近藤優和
////////////////////////////////////////////////////////////////////////////////

// ヘッダファイルの読み込み ================================================
#include "GameBase.h"
#include "..\System\Direct3D\Direct3D.h"
#include "..\System\FrameRateController\FrameRateController.h"
#include "..\System\Window\Window.h"
#include "..\Utility\ComHelper.h"



// 名前空間の使用宣言
using namespace std;




//------------------------------------------------------------------
//! @brief コンストラクタ
//!
//! @param
//------------------------------------------------------------------
GameBase::GameBase()
	: m_pFrameRateController(nullptr)
{
}



//------------------------------------------------------------------
//! @brief デストラクタ
//------------------------------------------------------------------
GameBase::~GameBase()
{
}





//------------------------------------------------------------------
//! @brief フレームレートの取得
//!
//! @param なし
//!
//! @return フレームレート
//------------------------------------------------------------------
double GameBase::GetFrameRate() const
{
	return m_pFrameRateController->GetFrameRate();
}



//------------------------------------------------------------------
//! @brief フレームレートの設定
//!
//! @param[in] frameRate フレームレート
//!
//! @return なし
//------------------------------------------------------------------
void GameBase::SetFrameRate(int frameRate)
{
	m_pFrameRateController->SetFrameRate(frameRate);
}




//-----------------------------------------------------------------
//! @brief ゲームの実行
//!
//! @param[in] screenMode 起動スクリーンモード
//!
//! @retval 終了コード 実行成功
//! @retval 0          実行失敗
//-----------------------------------------------------------------
int GameBase::Run(ScreenMode screenMode)
{
	// システムの初期化
	if (!InitializeSystem())
	{
		return 0;
	}


	// ゲームの初期化
	if (!Initialize())
	{
		Finalize();
		return 0;
	}


	// 指定のスクリーンモードで起動
	m_pDirect3D->SetFullscreenState(toBool(screenMode));


	// フレームレートの計測開始
	m_pFrameRateController->Start();


	// メッセージループ
	while (m_pWindow->HandleMessage())
	{
		// フレームレートの調整
		m_pFrameRateController->Adjust();


		// ゲームの更新
		Update();


		// ゲームの描画
		if (!m_pFrameRateController->IsSkipFrame())
		{
			Render();
		}
	}


	// ゲームの後始末
	Finalize();


	// ウィンドウ表示モードに移行
	m_pDirect3D->SetFullscreenState(toBool(ScreenMode::WINDOWED));


	// 終了コードの返却
	return m_pWindow->GetExitValue();
}



//-----------------------------------------------------------------
//! @brief システムの初期化
//!
//! @param なし
//!
//! @retval true  システムの初期化に成功
//! @retval false システムの初期化に失敗
//-----------------------------------------------------------------
bool GameBase::InitializeSystem()
{
	// ウィンドウの作成
	m_pWindow.reset(Window::GetInstance());
	if (!m_pWindow)
	{
		MessageBox(nullptr, L"ウィンドウの作成に失敗しました。", L"Error [Game]", MB_OK);
		return false;
	}

	// Direct3Dデバイスの作成
	m_pDirect3D.reset(Direct3D::GetInstance());
	if (!m_pDirect3D)
	{
		MessageBox(nullptr, L"Direct3D環境の構築に失敗しました。", L"Error [Game]", MB_OK);
		return false;
	}


	// フレームレート制御装置の作成
	m_pFrameRateController = make_unique<FrameRateController>();




	// システムの初期化に成功
	return true;
}