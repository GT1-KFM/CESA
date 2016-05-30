////////////////////////////////////////////////////////////////////
//! @file   GameMain.coo
//!
//! @brief  ゲームの派生クラスのソースファイル
//!
//! @date   2016/5/25
//!
//! @author 近藤　優和
////////////////////////////////////////////////////////////////////


// ヘッダファイルの読み込み ----------------------------------------
#include <WICTextureLoader.h>

#include "GameMain.h"
#include "..\System\Direct3D\direct3d.h"
#include "..\System\Window\Window.h"
#include "..\Utility\CommonStates\CommonStatesHelper.h"
#include "..\Scene\MyScene\TitleScene.h"
#include "..\Graphics\SpriteManager.h"
#include "..\Input\InputManager.h"
#include "..\System\Direct3D\Direct3D.h"


// 名前空間の使用宣言 ----------------------------------------------
using namespace std;
using namespace DirectX;




//------------------------------------------------------------------
//! @brief コンストラクタ
//------------------------------------------------------------------
GameMain::GameMain()
	: GameBase()
{
}



//------------------------------------------------------------------
//! @brief デストラクタ
//------------------------------------------------------------------
GameMain::~GameMain()
{

}



//------------------------------------------------------------------
//! @brief ゲームの初期化
//!
//! @param なし
//!
//! @retval true  初期化に成功
//! @retval false 初期化に失敗
//------------------------------------------------------------------
bool GameMain::Initialize()
{
	// フレームレートの設定(60FPS)
	SetFrameRate(60);

	// シーンマネージャの生成
	m_pSceneManager.reset(SceneManager::GetInstance());

	// 初めのシーンを設定する
	m_pSceneManager->SceneChange(TitleScene::GetInstance());

	InputManager::GetInstance()->OnKeyboard();


	// 初期化に成功
	return true;
}




//------------------------------------------------------------------
//! @brief ゲームの更新
//!
//! @param なし
//!
//! @return なし
//------------------------------------------------------------------
void GameMain::Update()
{
	// シーンマネージャの更新
	m_pSceneManager->Update();

}



//------------------------------------------------------------------
//! @brief ゲームの描画
//!
//! @param なし
//!
//! @return なし
//------------------------------------------------------------------
void GameMain::Render()
{
	// ダイレクト3Dの取得
	Direct3D* direct3D = Direct3D::GetInstance();

	// デバイスリソースの取得
	ID3D11DeviceContext*    pDeviceContext = direct3D->GetDeviceContext();
	ID3D11RenderTargetView* pRenderTargetView = direct3D->GetRenderTargetView();

	//深度バッファの取得
	ID3D11DepthStencilView*  pDepthStencilView = direct3D->GetDepthStencilView();
	IDXGISwapChain*         pSwapChain = direct3D->GetSwapChain();
	

	// レンダーターゲットのクリア
	pDeviceContext->ClearRenderTargetView(pRenderTargetView, Colors::DarkBlue);
	//深度バッファのクリア
	pDeviceContext->ClearDepthStencilView(pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);


	// シーンマネージャの描画
	m_pSceneManager->Render();


	// 画面のフリップ
	pSwapChain->Present(0, 0);


}



//------------------------------------------------------------------
//! @brief ゲームの後始末
//!
//! @param なし
//!
//! @return なし
//------------------------------------------------------------------
void GameMain::Finalize()
{
	m_pSceneManager->Finalize();
	CommonStatesHelper::Dispose();
	InputManager::Dispose();
}