////////////////////////////////////////////////////////////////////////////
//! @file   TitleScene.cpp
//!
//! @brief  タイトルシーンのソースファイル
//!
//! @date   2016/05/23
//!
//! @author 近藤　優和
////////////////////////////////////////////////////////////////////////////


// ヘッダファイルの読み込み ----------------------------------------
#include "TitleScene.h"
#include "PlayScene.h"


// 名前空間の使用宣言 ----------------------------------------------
using namespace std;
using namespace DirectX;
using namespace SimpleMath;




// 静的メンバ変数の定義 --------------------------------------------
const wchar_t* TitleScene::TITLE_PATH = L"Scene/Title.png";
Scene* TitleScene::pScene = nullptr;




//------------------------------------------------------------------
//! @brief コンストラクタ
//------------------------------------------------------------------
TitleScene::TitleScene()
{
	this->Initialize();
}





//------------------------------------------------------------------
//! @brief デストラクタ
//------------------------------------------------------------------
TitleScene::~TitleScene()
{

}






//------------------------------------------------------------------
//! @brief ゲームの初期化
//!
//! @param なし
//!
//! @retval なし
//------------------------------------------------------------------
void TitleScene::Initialize()
{

	// スプライトマネージャ
	m_pSpriteManager.reset(SpriteManager::GetInstance());

	// タイトルスプライトの生成
	m_pTitleSprite.reset(m_pSpriteManager->CreateSprite(TITLE_PATH));


}


//------------------------------------------------------------------
//! @brief		更新
//!
//! @param[in]	ChangeScene*	チェンジシーン
//!
//! @retval		なし
//------------------------------------------------------------------
void TitleScene::Update(ChangeScene* pChangeScene)
{
	//pChangeScene->SceneChange(PlayScene::GetInstance());

}




//------------------------------------------------------------------
//! @brief		描画
//!
//! @param		なし
//!
//! @retval		なし
//------------------------------------------------------------------
void TitleScene::Render()
{
	m_pSpriteManager->Render(m_pTitleSprite.get(), Vector2(0.0f, 0.0f));
}





//------------------------------------------------------------------
//! @brief		オブジェクトの破棄
//!
//! @param[in]	なし
//!
//! @retval		なし
//------------------------------------------------------------------
void TitleScene::Dispose()
{
	if (pScene != nullptr)
		delete pScene;
}