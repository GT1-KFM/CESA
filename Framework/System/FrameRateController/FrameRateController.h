//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   FrameRateController.h
//!
//! @brief  フレームレート制御クラスのヘッダファイル
//!
//! @date   2014/10/10
//!
//! @author 高木 晋
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// 多重インクルード防止 ====================================================
#pragma once




// ヘッダファイルの読み込み ================================================
#include <memory>

#include <Windows.h>

#include "Framework\Utility\Timer.h"




// クラス定義 ==============================================================

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//! @brief フレームレート制御クラス
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
class FrameRateController final
{
	// クラス内定数 --------------------------------------------
private:
	static const UINT DEFAULT_FRAME_RATE = 60;   //!< フレームレートの初期設定値



	// メンバ変数 ----------------------------------------------
private:
	std::unique_ptr<Timer> m_timer;    //!< タイマー

	double m_frameRate;           //!< 1秒あたりのフレーム数
	UINT   m_frameTime;           //!< 1フレームあたりの時間[ns]
	UINT   m_startTime;           //!< フレームの計測開始時間[ns]
	UINT   m_elapsedTime;         //!< フレーム経過時間[ns]
	UINT   m_totalElapsedTime;    //!< 総経過時間[ns]
	int    m_frameCount;          //!< フレーム数
	bool   m_isSkipFrame;         //!< スキップするフレームかどうか



	// コンストラクタ ------------------------------------------
public:
	FrameRateController(UINT frameRate = DEFAULT_FRAME_RATE);



	// デストラクタ --------------------------------------------
public:
	~FrameRateController() = default;



	// 属性 ----------------------------------------------------
public:
	// フレームレートの取得
	double GetFrameRate() const;

	// フレームレートの設定
	void SetFrameRate(UINT frameRate);



	// 操作 ----------------------------------------------------
public:
	// 計測開始
	void Start();

	// フレームレートの調整
	void Adjust();

	// スキップ対象のフレームかどうかの調査
	bool IsSkipFrame() const;



	// 内部実装 ------------------------------------------------
private:
	// フレーム待機
	void Wait();

	// フレームレートの更新
	void UpdateFrameRate();


};