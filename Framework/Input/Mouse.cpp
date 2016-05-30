//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Mouse.h
//!
//! @brief  マウスクラスのソースファイル
//!
//! @date   2014/10/10
//!
//! @author 高木 晋
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// ヘッダファイルの読み込み ================================================
#include "Mouse.h"

#include <commctrl.h>




// ライブラリの追加 ========================================================
#pragma comment(lib, "comctl32.lib")    // コモンコントロール用ライブラリ




// メンバ関数の定義 ========================================================
//------------------------------------------------------------------
//! @brief コンストラクタ
//!
//! @param なし
//------------------------------------------------------------------
Mouse::Mouse(HWND hWindow)
	: m_hWindow(hWindow)
	, m_lastState({ 0, 0,{ 0, 0 } })
	, m_currentState({ 0, 0,{ 0, 0 } })
{
	// ウィンドウのサブクラス化
	UINT_PTR  subclassID = reinterpret_cast<DWORD_PTR>(this);
	DWORD_PTR referenceData = reinterpret_cast<DWORD_PTR>(this);
	SetWindowSubclass(hWindow, Procedure, subclassID, referenceData);
}



//------------------------------------------------------------------
//! @brief デストラクタ
//------------------------------------------------------------------
Mouse::~Mouse()
{
	// ウィンドウのサブクラス化の解除
	UINT_PTR subclassID = reinterpret_cast<DWORD_PTR>(this);
	RemoveWindowSubclass(m_hWindow, Procedure, subclassID);
}



//------------------------------------------------------------------
//! @brief 指定されたボタンが押されているかどうかを判断
//!
//! @param[in] button 判定したいボタンの仮想ボタンコード
//!
//! @retval true  指定されたボタンが押されている場合
//! @retval false それ以外の場合
//------------------------------------------------------------------
bool Mouse::IsButtonDown(Button button) const
{
	return IsButtonDown(m_currentState, button);
}



//------------------------------------------------------------------
//! @brief 指定されたボタンが押されていないかどうかを判断
//!
//! @param[in] button 判定したいボタンの仮想ボタンコード
//!
//! @retval true  指定されたボタンが押されていない場合
//! @retval false それ以外の場合
//------------------------------------------------------------------
bool Mouse::IsButtonUp(Button button) const
{
	return !IsButtonDown(m_currentState, button);
}



//------------------------------------------------------------------
//! @brief 指定されたボタンが押されたかどうかを判断
//!
//! @param[in] button 判定したいボタンの仮想ボタンコード
//!
//! @retval true  指定されたボタンが押された場合
//! @retval false それ以外の場合
//------------------------------------------------------------------
bool Mouse::IsButtonPressed(Button button) const
{
	return IsButtonDown(m_currentState, button) && !IsButtonDown(m_lastState, button);
}



//------------------------------------------------------------------
//! @brief 指定されたボタンが離されたかどうかを判断
//!
//! @param[in] button 判定したいボタンの仮想ボタンコード
//!
//! @retval true  指定されたボタンが離された場合
//! @retval false それ以外の場合
//------------------------------------------------------------------
bool Mouse::IsButtonReleased(Button button) const
{
	return !IsButtonDown(m_currentState, button) && IsButtonDown(m_lastState, button);
}



//------------------------------------------------------------------
//! @brief ホイールの回転量(ノッチ)の取得
//!
//! @param なし
//!
//! @return ホイールの回転量(ノッチ)
//------------------------------------------------------------------
int Mouse::GetWheelDelta() const
{
	return m_currentState.wheelDelta / WHEEL_DELTA;
}



//------------------------------------------------------------------
//! @brief マウスポインタの座標の取得
//!
//! @param なし
//!
//! @return マウスポインタの座標
//------------------------------------------------------------------
POINT Mouse::GetPointerPosition() const
{
	return m_currentState.pointerPosition;
}



//------------------------------------------------------------------
//! @brief マウスポインタのX座標の取得
//!
//! @param なし
//!
//! @return マウスポインタのX座標
//------------------------------------------------------------------
LONG Mouse::GetPointerPositionX() const
{
	return m_currentState.pointerPosition.x;
}



//------------------------------------------------------------------
//! @brief マウスポインタのY座標の取得
//!
//! @param なし
//!
//! @return マウスポインタのY座標
//------------------------------------------------------------------
LONG Mouse::GetPointerPositionY() const
{
	return m_currentState.pointerPosition.y;
}



//------------------------------------------------------------------
//! @brief マウスの状態の更新
//!
//! @param なし
//!
//! @return なし
//------------------------------------------------------------------
void Mouse::Update()
{
	// 状態の履歴を保存
	m_lastState = m_currentState;

	// ボタンの現在の状態を取得
	m_currentState.buttonState = 0;

	if (GetKeyState(VK_LBUTTON) & 0x8000)
	{
		m_currentState.buttonState |= Button::LEFT;
	}

	if (GetKeyState(VK_RBUTTON) & 0x8000)
	{
		m_currentState.buttonState |= Button::RIGHT;
	}

	if (GetKeyState(VK_MBUTTON) & 0x8000)
	{
		m_currentState.buttonState |= Button::WHEEL;
	}


	// ホイールの回転量の取得
	m_currentState.wheelDelta = m_wheelDelta;
	m_wheelDelta = 0;


	// マウスポインターの座標の取得
	GetCursorPos(&m_currentState.pointerPosition);
	ScreenToClient(m_hWindow, &m_currentState.pointerPosition);
}



//------------------------------------------------------------------
//! @brief ホイールの状態の更新
//!
//! @param[in] wheelDelta ホイールの回転量
//!
//! @return なし
//------------------------------------------------------------------
void Mouse::UpdateWheel(int wheelDelta)
{
	m_wheelDelta += wheelDelta;
}



//------------------------------------------------------------------
//! @brief ある状態において指定されたボタンが押されているかどうかを判断
//!
//! @param[in] mouseState マウスの状態
//! @param[in] button     判定したいボタンの仮想キーコード
//!
//! @retval true  指定されたボタンが押されている場合
//! @retval false それ以外の場合
//------------------------------------------------------------------
inline bool Mouse::IsButtonDown(const MouseState& mouseState, Button button) const
{
	return (mouseState.buttonState & button) ? true : false;
}




// 静的メンバ関数の定義 ====================================================
//------------------------------------------------------------------
//! @brief マウス・プロシージャ
//!
//! @param[in] hWindow     ウィンドウハンドル
//! @param[in] uMessage    メッセージの識別子
//! @param[in] wParam      メッセージの1番目のパラメータ
//! @param[in] lParam      メッセージの2番目のパラメータ
//! @param[in] uIdSubclass サブクラスID
//! @param[in] dwRefData   参照データ
//!
//! @return メッセージ処理の結果(送信されたメッセージによって異なる)
//------------------------------------------------------------------
LRESULT CALLBACK Mouse::Procedure(HWND hWindow, UINT uMessage, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
	// メッセージの処理
	switch (uMessage)
	{
	case WM_MOUSEWHEEL:
	{
		Mouse* mouse = reinterpret_cast<Mouse*>(dwRefData);
		if (mouse)
		{
			mouse->UpdateWheel(GET_WHEEL_DELTA_WPARAM(wParam));
			return 0;
		}
		break;
	}
	}

	// 自分で処理しないメッセージはWindowsに任せる
	return DefSubclassProc(hWindow, uMessage, wParam, lParam);
}