////////////////////////////////////////////////////////////////////////////
//! @file   SceneManager.h
//!
//! @brief  シーンマネージャのヘッダファイル
//!
//! @date   2016/5/24
//!
//! @author 近藤　優和
////////////////////////////////////////////////////////////////////////////


// 多重インクルード防止 ---------------------------------------------------
#pragma once



// ヘッダファイルの読み込み ------------------------------------------------
#include "Scene.h"
#include <string>
#include "ChangeScene.h"
#include "MyScene\TitleScene.h"
#include "MyScene\PlayScene.h"
#include "Framework\Graphics\SpriteManager.h"



// ---------------------------------------------------------------------------
// SceneManagerクラス
// ---------------------------------------------------------------------------
class SceneManager	: public ChangeScene
{

	// 静的メンバ変数 -----------------------------------------------------
private:

	static SceneManager*			m_pSceneManager;		// SceneManager
	static const wchar_t*			FADE_DISPLAY;			// フェード用画像パス
	static const float			FADE_ALPHA_MAX;			// フェードする最大時間
	static const float			FADE_ALPHA_MIN;			// フェードする最小時間　
	static const float			FADE_SPPED;				// フェードのスピード

	// メンバ変数 ---------------------------------------------------------
private:
	
	Scene*							m_pCurrentScene;		// 現在のシーン
	Scene*							m_pNextScene;			// 次のシーン
	std::unique_ptr<SpriteManager>	m_pSpriteManager;	// スプライトマネージャ
	std::unique_ptr<Sprite>			m_pFadeSprite;			// フェード用スプライト
	bool							m_fadeInFlag;			// フェードインのタイミング
	bool							m_fadeOutFlag;			// フェードアウトのタイミング
	float							m_alpha;				// 透過色


	// コンストラクタ ---------------------------------------------------------
private:

	SceneManager();


	// デストラクタ -----------------------------------------------------------
public:

	 ~SceneManager();


	// 静的メンバ関数 ---------------------------------------------------------
public:


	// ---------------------------------------------------------------------------
	//! @brief      シーンマネージャへのアドレスを取得する
	//
	//! @param		なし
	//!
	//! @return     pSceneManager
	// ---------------------------------------------------------------------------
	static SceneManager* GetInstance()
	{
		// 空の場合SceneManagerを生成する
		if (m_pSceneManager == nullptr)
			m_pSceneManager = new SceneManager();

		return m_pSceneManager;
	}

	// メンバ関数 -------------------------------------------------------------
public:

	// 初期化
	void Initialize();

	// 更新
	void Update();

	// 描画
	void Render();

	// 後始末
	void Finalize();

	//
	void FadeIn();

	//
	void FadeOut();

	// シーンの変更
	void SceneChange(Scene* currentScene) override;

};
