//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Gamepad.h
//!
//! @brief  ゲームパッド(Xbox 360 コントローラー)クラスのソースファイル
//!
//! @date   2014/10/10
//!
//! @author 高木 晋
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// ヘッダファイルの読み込み ================================================
#include "Gamepad.h"




// ライブラリの追加 ========================================================
#pragma comment(lib, "Xinput9_1_0.lib")    // Xinput用ライブラリ




// メンバ関数の定義 ========================================================
//------------------------------------------------------------------
//! @brief コンストラクタ
//!
//! @param なし
//------------------------------------------------------------------
Gamepad::Gamepad(DWORD userIndex)
	: m_userIndex(userIndex)
	, m_lastState({ false,{ 0 } })
	, m_currentState({ false,{ 0 } })
{
}



//------------------------------------------------------------------
//! @brief ゲームパッドが接続されているかどうかを判断
//!
//! @param なし
//!
//! @retval true  接続されている場合
//! @retval false それ以外の場合
//------------------------------------------------------------------
bool Gamepad::IsConnected() const
{
	return m_currentState.isConnected;
}



//------------------------------------------------------------------
//! @brief 指定されたボタンが押されているかどうかを判断
//!
//! @param[in] button 判定したいボタンの仮想ボタンコード
//!
//! @retval true  指定されたボタンが押されている場合
//! @retval false それ以外の場合
//------------------------------------------------------------------
bool Gamepad::IsButtonDown(Button button) const
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
bool Gamepad::IsButtonUp(Button button) const
{
	return !IsButtonDown(m_currentState, button);
}



//------------------------------------------------------------------
//! @brief 指定されたボタンが押されたかどうかを判断
//!
//! @param[in] button 判定したいボタンの仮想ボタンコード
//!
//! @retval true  指定されたキーが押された場合
//! @retval false それ以外の場合
//------------------------------------------------------------------
bool Gamepad::IsButtonPressed(Button button) const
{
	return IsButtonDown(m_currentState, button) && !IsButtonDown(m_lastState, button);
}



//------------------------------------------------------------------
//! @brief 指定されたボタンが離されたかどうかを判断
//!
//! @param[in] button 判定したいボタンの仮想ボタンコード
//!
//! @retval true  指定されたキーが離された場合
//! @retval false それ以外の場合
//------------------------------------------------------------------
bool Gamepad::IsButtonReleased(Button button) const
{
	return !IsButtonDown(m_currentState, button) && IsButtonDown(m_lastState, button);
}



//------------------------------------------------------------------
//! @brief 左スティックのX軸の値の取得
//!
//! @param なし
//!
//! @return 左スティックのX軸の値(-1.0～1.0)
//------------------------------------------------------------------
float Gamepad::GetLeftThumbX() const
{
	return NormalizeThumb(m_currentState.state.Gamepad.sThumbLX);
}



//------------------------------------------------------------------
//! @brief 左スティックのY軸の値の取得
//!
//! @param なし
//!
//! @return 左スティックのY軸の値(-1.0～1.0)
//------------------------------------------------------------------
float Gamepad::GetLeftThumbY() const
{
	return NormalizeThumb(m_currentState.state.Gamepad.sThumbLY);
}



//------------------------------------------------------------------
//! @brief 右スティックのX軸の値の取得
//!
//! @param なし
//!
//! @return 右スティックのX軸の値(-1.0～1.0)
//------------------------------------------------------------------
float Gamepad::GetRightThumbX() const
{
	return NormalizeThumb(m_currentState.state.Gamepad.sThumbRX);
}



//------------------------------------------------------------------
//! @brief 右スティックのY軸の値の取得
//!
//! @param なし
//!
//! @return 右スティックのY軸の値(-1.0～1.0)
//------------------------------------------------------------------
float Gamepad::GetRightThumbY() const
{
	return NormalizeThumb(m_currentState.state.Gamepad.sThumbRY);
}



//------------------------------------------------------------------
//! @brief 左トリガーの値の取得
//!
//! @param なし
//!
//! @return 左トリガーの値(0.0～1.0)
//------------------------------------------------------------------
float Gamepad::GetLeftTrigger() const
{
	return NormalizeTrigger(m_currentState.state.Gamepad.bLeftTrigger);
}



//------------------------------------------------------------------
//! @brief 右トリガーの値の取得
//!
//! @param なし
//!
//! @return 右トリガーの値(0.0～1.0)
//------------------------------------------------------------------
float Gamepad::GetRightTrigger() const
{
	return NormalizeTrigger(m_currentState.state.Gamepad.bRightTrigger);
}



//------------------------------------------------------------------
//! @brief ゲームパッドの状態の更新
//!
//! @param なし
//!
//! @return なし
//------------------------------------------------------------------
void Gamepad::Update()
{
	// 状態の履歴を保存
	m_lastState = m_currentState;


	// ゲームパッドの現在の状態を取得
	DWORD result = XInputGetState(m_userIndex, &m_currentState.state);

	if (result == ERROR_SUCCESS)
	{
		m_currentState.isConnected = true;

		AdjustThumb();
		AdjustTrigger();
	}
	else
	{
		m_currentState.isConnected = false;
	}
}



//------------------------------------------------------------------
//! @brief ある状態において指定されたボタンが押されているかどうかを判断
//!
//! @param[in] state  ゲームパッドの状態
//! @param[in] button 判定したいボタンの仮想ボタンコード
//!
//! @retval true  指定されたキーが押されている場合
//! @retval false それ以外の場合
//------------------------------------------------------------------
inline bool Gamepad::IsButtonDown(const GamepadState& gamepadState, Button button) const
{
	return (gamepadState.state.Gamepad.wButtons & button) ? true : false;
}



//------------------------------------------------------------------
//! @brief スティックの値の調整
//!
//! @param なし
//!
//! @return なし
//------------------------------------------------------------------
void Gamepad::AdjustThumb()
{
	// 左スティックの値の調整
	AdjustThumb(&m_currentState.state.Gamepad.sThumbLX);
	AdjustThumb(&m_currentState.state.Gamepad.sThumbLY);


	// 右スティックの値の調整
	AdjustThumb(&m_currentState.state.Gamepad.sThumbRX);
	AdjustThumb(&m_currentState.state.Gamepad.sThumbRY);
}



//------------------------------------------------------------------
//! @brief スティックの各軸の値の調整
//!
//! @param[in] thumb 値を調整するスティックの軸
//!
//! @return なし
//------------------------------------------------------------------
void Gamepad::AdjustThumb(SHORT* thumb)
{
	// 左スティックのX軸の値の調整
	if (*thumb <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
		*thumb > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
	{
		*thumb = 0;
	}
	else if (*thumb < -THUMB_LIMIT)
	{
		*thumb = -THUMB_LIMIT;
	}
}



//------------------------------------------------------------------
//! @brief スティックの値の正規化
//!
//! @param thumb
//!
//! @return -1.0～1.0に正規化したスティックの値
//------------------------------------------------------------------
inline float Gamepad::NormalizeThumb(SHORT thumb) const
{
	return thumb / static_cast<float>(THUMB_LIMIT);
}



//------------------------------------------------------------------
//! @brief トリガーの値の調整
//!
//! @param なし
//!
//! @return なし
//------------------------------------------------------------------
void Gamepad::AdjustTrigger()
{
	// 左トリガーの値の調整
	if (m_currentState.state.Gamepad.bLeftTrigger < XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
	{
		m_currentState.state.Gamepad.bLeftTrigger = 0;
	}


	// 右トリガーの値の調整
	if (m_currentState.state.Gamepad.bRightTrigger < XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
	{
		m_currentState.state.Gamepad.bRightTrigger = 0;
	}
}



//------------------------------------------------------------------
//! @brief トリガーの値の正規化
//!
//! @param trigger
//!
//! @return 0.0～1.0に正規化したトリガーの値
//------------------------------------------------------------------
inline float Gamepad::NormalizeTrigger(BYTE trigger) const
{
	return trigger / static_cast<float>(TRIGGER_MAX);
}