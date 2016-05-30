////////////////////////////////////////////////////////////////////////////
//! @file   GameBase.h
//!
//! @brief  ゲームの基本クラスのヘッダファイル
//!
//! @date   
//!
//! @author 近藤　優和
////////////////////////////////////////////////////////////////////////////

// 多重インクルード防止 
#pragma once




// ヘッダファイルの読み込み 
#include <memory>
#include <string>

#include <Windows.h>

#include <d3d11.h>

#include "ScreenMode.h"




// クラス宣言
class Window;
class Direct3D;
class FrameRateController;




// ---------------------------------------------------------------------------
// GameBaseクラス
// ---------------------------------------------------------------------------
class GameBase
{
	// メンバ変数 ----------------------------------------------
private:


	std::unique_ptr<Window>              m_pWindow;                 //!< ウィンドウ
	std::unique_ptr<Direct3D>            m_pDirect3D;               //!< Direct3D

	std::unique_ptr<FrameRateController> m_pFrameRateController;    //!< フレームレート制御装置



	// コンストラクタ ------------------------------------------
public:
	GameBase();



	// デストラクタ --------------------------------------------
public:
	virtual ~GameBase();



	// 属性 ----------------------------------------------------
public:

	// フレームレートの取得
	double GetFrameRate() const;

	// フレームレートの設定
	void SetFrameRate(int frameRate);



	// 操作 ----------------------------------------------------
public:

	// ゲームの実行
	int Run(ScreenMode screenMode);



	// 内部実装 ------------------------------------------------
private:

	// システムの初期化
	bool InitializeSystem();

	// 初期化
	virtual bool Initialize() = 0;

	// 更新
	virtual void Update() = 0;

	// 描画
	virtual void Render() = 0;

	// 後始末
	virtual void Finalize() = 0;


};