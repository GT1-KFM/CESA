//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   FrameRateController.cpp
//!
//! @brief  フレームレート制御クラスのソースファイル
//!
//! @date   2014/10/10
//!
//! @author 高木 晋
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// ヘッダファイルの読み込み ================================================
#include "FrameRateController.h"




// メンバ関数の定義 ========================================================
//------------------------------------------------------------------
//! @brief コンストラクタ
//!
//! @param frameRate フレームレート
//------------------------------------------------------------------
FrameRateController::FrameRateController(UINT frameRate)
	: m_timer(new Timer)
	, m_frameRate(0)
	, m_frameTime(0)
	, m_startTime(0)
	, m_elapsedTime(0)
	, m_totalElapsedTime(0)
	, m_frameCount(0)
	, m_isSkipFrame(false)
{
	SetFrameRate(frameRate);
}



//------------------------------------------------------------------
//! @brief フレームレートの取得
//!
//! @param なし
//!
//! @return フレームレート
//------------------------------------------------------------------
double FrameRateController::GetFrameRate() const
{
	return m_frameRate;
}



//------------------------------------------------------------------
//! @brief フレームレートの設定
//!
//! @param[in] frameRate フレームレート
//!
//! @return なし
//------------------------------------------------------------------
void FrameRateController::SetFrameRate(UINT frameRate)
{
	m_frameTime = Timer::ONE_SECOND / frameRate;
}



//------------------------------------------------------------------
//! @brief フレームレート計測の開始
//!
//! @param なし
//!
//! @return なし
//------------------------------------------------------------------
void FrameRateController::Start()
{
	m_timer->Reset();
	m_startTime = m_timer->GetTime();
}



//------------------------------------------------------------------
//! @brief フレームレートの調整
//!
//! @param なし
//!
//! @return なし
//------------------------------------------------------------------
void FrameRateController::Adjust()
{
	// 1フレームに掛かった時間の計測
	m_elapsedTime = m_timer->GetTime() - m_startTime;


	// フレームレートの調整
	if (m_elapsedTime < m_frameTime)
	{
		m_isSkipFrame = false;

		Wait();
	}
	else
	{
		m_isSkipFrame = true;
	}


	// フレームレートの更新
	UpdateFrameRate();


	// フレームの計測開始時間の更新
	m_startTime = m_timer->GetTime();
}



//------------------------------------------------------------------
//! @brief スキップ対象のフレームかどうかの調査
//!
//! @param なし
//!
//! @retval true  スキップ対象のフレーム
//! @retval false スキップ対象でないフレーム
//------------------------------------------------------------------
bool FrameRateController::IsSkipFrame() const
{
	return m_isSkipFrame;
}



//------------------------------------------------------------------
//! @brief フレーム待機
//!
//! @param なし
//!
//! @return なし
//------------------------------------------------------------------
void FrameRateController::Wait()
{
	Sleep(0);

	while (m_elapsedTime < m_frameTime)
	{
		_mm_pause();
		m_elapsedTime = m_timer->GetTime() - m_startTime;
	}
}



//------------------------------------------------------------------
//! @brief フレームレートの更新
//!
//! @param なし
//!
//! @return なし
//------------------------------------------------------------------
void FrameRateController::UpdateFrameRate()
{
	m_frameCount++;
	m_totalElapsedTime += m_elapsedTime;

	if (m_totalElapsedTime >= Timer::ONE_SECOND)
	{
		m_frameRate = static_cast<double>(m_frameCount * Timer::ONE_SECOND) / m_totalElapsedTime;

		m_frameCount = 0;
		m_totalElapsedTime = 0;
	}
}
