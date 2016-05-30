////////////////////////////////////////////////////////////////////////////
//! @file   TitleScene.cpp
//!
//! @brief  タイトルシーンのソースファイル
//!
//! @date   2016/05/27
//!
//! @author 近藤　優和
////////////////////////////////////////////////////////////////////////////


// ヘッダファイルの読み込み ----------------------------------------
#include "TitleScene.h"
#include "PlayScene.h"
#include "Framework\Input\InputManager.h"



// 名前空間の使用宣言 ----------------------------------------------
using namespace std;
using namespace DirectX;
using namespace SimpleMath;




// 静的メンバ変数の定義 --------------------------------------------
Scene* TitleScene::pScene = nullptr;
const wchar_t* TitleScene::TITLE_PATH = L"Scene/Title.png";




//------------------------------------------------------------------
//! @brief		コンストラクタ
//------------------------------------------------------------------
TitleScene::TitleScene()
{
	this->Initialize();
}





//------------------------------------------------------------------
//! @brief		デストラクタ
//------------------------------------------------------------------
TitleScene::~TitleScene()
{

}






//------------------------------------------------------------------
//! @brief		ゲームの初期化
//------------------------------------------------------------------
void TitleScene::Initialize()
{

	// スプライトマネージャ
	auto sprite = SpriteManager::GetInstance();


	// タイトルスプライトの生成
	m_pTitleSprite.reset(sprite->CreateSprite(TITLE_PATH));



}


//------------------------------------------------------------------
//! @brief		更新
//!
//! @param[in]	ChangeScene*	シーンの変更
//------------------------------------------------------------------
void TitleScene::Update(ChangeScene* pChangeScene)
{
	auto inputManager = InputManager::GetInstance();



	if (inputManager->GetKeyboard()->IsKeyDown(VK_SPACE))
	{
		pChangeScene->SceneChange(PlayScene::GetInstance());

	}

	inputManager->Update();
}




//------------------------------------------------------------------
//! @brief		描画
//------------------------------------------------------------------
void TitleScene::Render()
{
	auto sprite = SpriteManager::GetInstance();

	SpriteManager::GetInstance()->Render(m_pTitleSprite.get(), Vector2(0.0f, 0.0f));
}





//------------------------------------------------------------------
//! @brief		オブジェクトの破棄
//------------------------------------------------------------------
void TitleScene::Dispose()
{
	if (pScene != nullptr)
		delete pScene;
	
}