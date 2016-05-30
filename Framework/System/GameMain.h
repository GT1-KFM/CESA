////////////////////////////////////////////////////////////////////////////
//! @file   GameMain.h
//!
//! @brief  ゲームの派生クラスのヘッダファイル
//!
//! @date   2016/5/19
//!
//! @author 近藤　優和
////////////////////////////////////////////////////////////////////////////


// 多重インクルード防止 
#pragma once




// ヘッダファイルの読み込み 
#include "..\System\GameBase.h"
#include<CommonStates.h>
#include"Effects.h"
#include "Model.h"
#include "..\Input\InputManager.h"
#include "..\Graphics\SpriteManager.h"	
#include "..\Scene\SceneManager.h"
#include "Framework\Camera\Camera.h"


// ---------------------------------------------------------------------------
// GameMainクラス
// ---------------------------------------------------------------------------
class GameMain : public GameBase
{
	static const int ENEMY_NUM = 1;



	// メンバ変数 ----------------------------------------------
private:

	std::unique_ptr<SceneManager>	m_pSceneManager;	// シーンマネージャ
	std::unique_ptr<Camera>			m_pCamera;			// カメラ



	// コンストラクタ ------------------------------------------
public:
	GameMain();



	// デストラクタ --------------------------------------------
public:
	~GameMain();



	// 操作 ----------------------------------------------------
public:
	// 初期化
	bool Initialize();

	// 更新
	void Update();

	// 描画
	void Render();

	// 後始末
	void Finalize();
};
