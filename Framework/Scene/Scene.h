////////////////////////////////////////////////////////////////////////////
//! @file   Scene.h
//!
//! @brief  シーンのヘッダファイル
//!
//! @date   2016/5/19
//!
//! @author 近藤　優和
////////////////////////////////////////////////////////////////////////////


// 多重インクルード防止 ----------------------------------------------------
#pragma once

// 前方宣言
class ChangeScene;


//----------------------------------------------------------------------------
// Scenerクラス
//----------------------------------------------------------------------------
class Scene
{

	// メンバ関数 ------------------------------------------------------------
public:

	// 仮想デストラクタ
	virtual ~Scene() {}

	// 初期化
	virtual void Initialize() = 0;

	// 更新
	virtual void Update(ChangeScene* pChangeScene) = 0;

	// 描画
	virtual void Render() = 0;

};