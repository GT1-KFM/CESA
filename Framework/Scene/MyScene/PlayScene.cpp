////////////////////////////////////////////////////////////////////////////
//! @file   PlayScene.cpp
//!
//! @brief  プレイシーンのソースファイル
//!
//! @date   2016/05/25
//!
//! @author 近藤　優和
////////////////////////////////////////////////////////////////////////////


// ヘッダファイルの読み込み ------------------------------------------------
#include "PlayScene.h"
#include "TitleScene.h"
#include "..\SceneManager.h"
#include "Framework\Input\InputManager.h"
#include "Framework\Graphics\Obj3D.h"
#include "Framework\System\Direct3D\Direct3D.h"
#include "Framework\Utility\CommonStates\CommonStatesHelper.h"
#include "Framework\System\Window\Window.h"


// 名前空間の使用宣言 ------------------------------------------------------
using namespace std;
using namespace DirectX;


// 静的メンバ変数の実体 ----------------------------------------------------
Scene* PlayScene::pScene = nullptr;


// -------------------------------------------------------------------------
//! @brief     コンストラクタ
// -------------------------------------------------------------------------
 PlayScene::PlayScene()
{
	this->Initialize();
}




 // ------------------------------------------------------------------------
 //! @brief     デストラクタ
 // ------------------------------------------------------------------------
 PlayScene::~PlayScene()
 {
 }





// -------------------------------------------------------------------------
//! @brief     初期化
// -------------------------------------------------------------------------
void PlayScene::Initialize()
{



}


// -------------------------------------------------------------------------
//! @brief      更新
//!
//! @param[in]	チェンジシーン
// -------------------------------------------------------------------------
void PlayScene::Update(ChangeScene* pChangeScene)
{

	auto inputManager = InputManager::GetInstance();
	inputManager->Update();


	//<! テスト
	// 　シーンを切り替える　
	if (inputManager->GetKeyboard()->IsKeyDown(VK_SPACE))
	{
		pChangeScene->SceneChange(TitleScene::GetInstance());
	}

}

// -------------------------------------------------------------------------
//! @brief      描画
// -------------------------------------------------------------------------
void PlayScene::Render()
{

	
}






// -------------------------------------------------------------------------
// オブジェクトを破棄
//--------------------------------------------------------------------------
void PlayScene::Dispose()
{
	if (pScene != nullptr)
		delete pScene;
}



