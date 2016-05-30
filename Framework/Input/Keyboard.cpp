//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Keyboard.cpp
//!
//! @brief  キーボードクラスのソースファイル
//!
//! @date   2014/10/10
//!
//! @author 高木 晋
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// ヘッダファイルの読み込み ================================================
#include "Keyboard.h"




// メンバ関数の定義 ========================================================
//------------------------------------------------------------------
//! @brief コンストラクタ
//!
//! @param なし
//------------------------------------------------------------------
Keyboard::Keyboard()
	: m_lastState({ { 0 } })
	, m_currentState({ { 0 } })
{
}



//------------------------------------------------------------------
//! @brief 指定されたキーが押されているかどうかを判断
//!
//! @param[in] key 判定したいキーの仮想キーコード
//!
//! @retval true  指定されたキーが押されている場合
//! @retval false それ以外の場合
//------------------------------------------------------------------
bool Keyboard::IsKeyDown(BYTE key) const
{
	return IsKeyDown(m_currentState, key);
}



//------------------------------------------------------------------
//! @brief 指定されたキーが押されていないかどうかを判断
//!
//! @param[in] key 判定したいキーの仮想キーコード
//!
//! @retval true  指定されたキーが押されていない場合
//! @retval false それ以外の場合
//------------------------------------------------------------------
bool Keyboard::IsKeyUp(BYTE key) const
{
	return !IsKeyDown(m_currentState, key);
}



//------------------------------------------------------------------
//! @brief 指定されたキーが押されたかどうかを判断
//!
//! @param[in] key 判定したいキーの仮想キーコード
//!
//! @retval true  指定されたキーが押された場合
//! @retval false それ以外の場合
//------------------------------------------------------------------
bool Keyboard::IsKeyPressed(BYTE key) const
{
	return IsKeyDown(m_currentState, key) && !IsKeyDown(m_lastState, key);
}



//------------------------------------------------------------------
//! @brief 指定されたキーが離されたかどうかを判断
//!
//! @param[in] key 判定したいキーの仮想キーコード
//!
//! @retval true  指定されたキーが離された場合
//! @retval false それ以外の場合
//------------------------------------------------------------------
bool Keyboard::IsKeyReleased(BYTE key) const
{
	return !IsKeyDown(m_currentState, key) && IsKeyDown(m_lastState, key);
}



//------------------------------------------------------------------
//! @brief キーボードの状態の更新
//!
//! @param なし
//!
//! @return なし
//------------------------------------------------------------------
void Keyboard::Update()
{
	// 状態の履歴を保存
	m_lastState = m_currentState;

	// キーボードの現在の状態を取得
	GetKeyboardState(m_currentState.keyState);
}



//******************************************************************
//! @brief ある状態において指定されたキーが押されているかどうかを判断
//!
//! @param[in] state キーボードの状態
//! @param[in] key   判定したいキーの仮想キーコード
//!
//! @retval true  指定されたキーが押されている場合
//! @retval false それ以外の場合
//******************************************************************
inline bool Keyboard::IsKeyDown(const KeyboardState& keyboardState, BYTE key) const
{
	return (keyboardState.keyState[key] & 0x80) ? true : false;
}