//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Timer.cpp
//!
//! @brief  時間計測クラスのソースファイル
//!
//! @date   2014/10/10
//!
//! @author 高木 晋
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// ヘッダファイルの読み込み ================================================
#include "Timer.h"




// 静的メンバ変数の定義 ====================================================
LARGE_INTEGER Timer::s_frequency = { 0 };




// メンバ関数の定義 ========================================================
//------------------------------------------------------------------
//! @brief コンストラクタ
//!
//! @param なし
//------------------------------------------------------------------
Timer::Timer()
{
	if (s_frequency.QuadPart == 0)
	{
		// CPU周波数の取得
		QueryPerformanceFrequency(&s_frequency);
	}


	// 計測開始カウントの設定
	QueryPerformanceCounter(&m_startCount);
}



//------------------------------------------------------------------
//! @brief 時間[ns]の取得
//!
//! @param なし
//!
//! @return 計測開始時刻からの経過時間によって表される現在の時間[ns]
//------------------------------------------------------------------
UINT Timer::GetTime() const
{
	LARGE_INTEGER currentCount;
	QueryPerformanceCounter(&currentCount);

	LONGLONG elapsedTime = currentCount.QuadPart - m_startCount.QuadPart;

	return static_cast<UINT>(elapsedTime * ONE_SECOND / s_frequency.QuadPart);
}



//------------------------------------------------------------------
//! @brief 計測開始時間のリセット
//!
//! @param なし
//!
//! @return なし
//------------------------------------------------------------------
void Timer::Reset()
{
	QueryPerformanceCounter(&m_startCount);
}
