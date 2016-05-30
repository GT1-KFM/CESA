////////////////////////////////////////////////////////////////////////////
//! @file   SceneManager.cpp
//!
//! @brief  シーンマネージャのソースファイル
//!
//! @date   2016/5/25
//!
//! @author 近藤　優和
////////////////////////////////////////////////////////////////////////////


// ヘッダファイルの読み込み -------------------------------------------------
#include "SceneManager.h"
using namespace DirectX;
using namespace SimpleMath;


// 名前空間の使用宣言 -------------------------------------------------------
using namespace std;



// 静的メンバ変数の実体を宣言------------------------------------------------
SceneManager* SceneManager::m_pSceneManager = nullptr;
const wchar_t* SceneManager::FADE_DISPLAY = L"Scene/BlackDisplay.png";
const float	SceneManager::FADE_ALPHA_MAX = 2.0f;
const float	SceneManager::FADE_ALPHA_MIN = 0.0f;
const float SceneManager::FADE_SPPED = 0.1f;






// ---------------------------------------------------------------------------
//! @brief     コンストラクタ
// ---------------------------------------------------------------------------
SceneManager::SceneManager()
{
	this->Initialize();
}




// ---------------------------------------------------------------------------
//! @brief     デストラクタ
// ---------------------------------------------------------------------------
SceneManager::~SceneManager()
{

}





// ---------------------------------------------------------------------------
//! @brief      初期化
// ---------------------------------------------------------------------------
void SceneManager::Initialize()
{
	// スプライトマネージャ
	m_pSpriteManager.reset(SpriteManager::GetInstance());

	// 現在のシーンを初期化
	m_pCurrentScene = nullptr;

	//フェード用画像
	m_pFadeSprite.reset(m_pSpriteManager->CreateSprite(FADE_DISPLAY));
	//透過色を設定
	m_alpha = 1.0f;

	// 次のシーンを初期化
	m_pNextScene = nullptr;

	// フェードフラグをオフ
	m_fadeInFlag = false;
	m_fadeOutFlag = false;
}





// ---------------------------------------------------------------------------
//! @brief      更新
// ---------------------------------------------------------------------------
void SceneManager::Update()
{
	// シーンを更新
	m_pCurrentScene->Update(this);

	// フェードを実行
	this->FadeOut();
	this->FadeIn();

}




// ---------------------------------------------------------------------------
//! @brief      描画
// ---------------------------------------------------------------------------
void SceneManager::Render()
{
	m_pCurrentScene->Render();

	// フェードを描画
	if (m_fadeInFlag || m_fadeOutFlag)
	{
		m_pSpriteManager->Render(m_pFadeSprite.get(), Vector2(0.0f, 0.0f));
	}

}





// ---------------------------------------------------------------------------
//! @brief      後始末
// ---------------------------------------------------------------------------
void SceneManager::Finalize()
{
	TitleScene::Dispose();
	PlayScene::Dispose();
}




// ---------------------------------------------------------------------------
//! @brief      フェードイン
// ---------------------------------------------------------------------------
void SceneManager::FadeIn()
{
	if (m_alpha >= FADE_ALPHA_MIN && m_fadeInFlag)
	{
		m_pFadeSprite->SetAlpha(m_alpha);
		m_alpha -= FADE_SPPED;
	}
	// フェードが終了していた場合フラグをオフ
	else if (m_alpha <= FADE_ALPHA_MIN)
	{
		m_fadeInFlag = false;
	}
}






// ---------------------------------------------------------------------------
//! @brief      フェードアウト
// ---------------------------------------------------------------------------
void SceneManager::FadeOut()
{
	if (m_alpha <= FADE_ALPHA_MAX && m_fadeOutFlag)
	{
		m_alpha += FADE_SPPED;
		m_pFadeSprite->SetAlpha(m_alpha);
	}
	// フェードが終了していた場合フラグをオフ
	else if(m_alpha >= FADE_ALPHA_MAX)
	{
		m_fadeOutFlag = false;
		m_fadeInFlag = true;
		m_pCurrentScene = m_pNextScene;
	}
}






// ---------------------------------------------------------------------------
//! @brief      シーンの変更
// ---------------------------------------------------------------------------
void SceneManager::SceneChange(Scene* currentScene)
{
	// 一番初めのシーン
	if (m_pNextScene == nullptr)
	{
		m_pCurrentScene = currentScene;
		m_pNextScene = m_pCurrentScene;
		return;
	}

	if (currentScene != m_pNextScene)
	{
		m_alpha = FADE_ALPHA_MIN;
		m_pNextScene = currentScene;
		m_fadeOutFlag = true;
		m_fadeInFlag = false;
	}
}