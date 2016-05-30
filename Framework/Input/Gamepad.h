//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Gamepad.h
//!
//! @brief  ゲームパッド(Xbox 360 コントローラー)クラスのヘッダファイル
//!
//! @date   2014/10/10
//!
//! @author 高木 晋
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// 多重インクルード防止 ====================================================
#pragma once




// ヘッダファイルの読み込み ================================================
#include <Windows.h>
#include <Xinput.h>




// クラス定義 ==============================================================
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//! @brief ゲームパッド(Xbox 360 コントローラー)クラス
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
class Gamepad
{
	// クラス内定数 --------------------------------------------
public:
	//! @brief 仮想ボタンコード
	enum Button : WORD
	{
		UP = XINPUT_GAMEPAD_DPAD_UP,
		DOWN = XINPUT_GAMEPAD_DPAD_DOWN,
		LEFT = XINPUT_GAMEPAD_DPAD_LEFT,
		RIGHT = XINPUT_GAMEPAD_DPAD_RIGHT,
		START = XINPUT_GAMEPAD_START,
		BACK = XINPUT_GAMEPAD_BACK,
		L_THUMB = XINPUT_GAMEPAD_LEFT_THUMB,
		R_THUMB = XINPUT_GAMEPAD_RIGHT_THUMB,
		L_SHOULDER = XINPUT_GAMEPAD_LEFT_SHOULDER,
		R_SHOULDER = XINPUT_GAMEPAD_RIGHT_SHOULDER,
		A = XINPUT_GAMEPAD_A,
		B = XINPUT_GAMEPAD_B,
		X = XINPUT_GAMEPAD_X,
		Y = XINPUT_GAMEPAD_Y,
	};

	static const int TRIGGER_MAX = 255;    //!< トリガーの最大値
	static const int THUMB_LIMIT = 32767;    //!< スティックの上下限(±)



											 // クラス内クラス ------------------------------------------
private:
	//! @brief ゲームパッド状態クラス
	struct GamepadState
	{
		bool         isConnected;    //!< 接続の有無
		XINPUT_STATE state;          //!< ゲームパッドの状態
	};



	// メンバ変数 ----------------------------------------------
private:
	DWORD m_userIndex;    //!< ユーザーのゲームパッドのインデックス

	GamepadState m_lastState;       //!< 前回のゲームパッドの状態
	GamepadState m_currentState;    //!< 現在のゲームパッドの状態



									// コンストラクタ ------------------------------------------
public:
	explicit Gamepad(DWORD userIndex = 0);



	// デストラクタ --------------------------------------------
public:
	~Gamepad() = default;



	// 属性 ----------------------------------------------------
public:
	// ゲームパッドが接続されているかどうかを判断
	bool IsConnected() const;


	// 指定されたボタンが押されているかどうかを判断
	bool IsButtonDown(Button button) const;

	// 指定されたボタンが押されていないかどうかを判断
	bool IsButtonUp(Button button) const;

	// 指定されたボタンが押されたかどうかを判断
	bool IsButtonPressed(Button button) const;

	// 指定されたボタンが離されたかどうかを判断
	bool IsButtonReleased(Button button) const;


	// 左スティックのX軸の値の取得
	float GetLeftThumbX() const;

	// 左スティックのY軸の値の取得
	float GetLeftThumbY() const;

	// 右スティックのX軸の値の取得
	float GetRightThumbX() const;

	// 右スティックのY軸の値の取得
	float GetRightThumbY() const;


	// 左トリガーの値の取得
	float GetLeftTrigger() const;

	// 右トリガーの値の取得
	float GetRightTrigger() const;



	// 操作 ----------------------------------------------------
public:
	// ゲームパッドの状態の更新
	void Update();



	// 内部実装 ------------------------------------------------
private:
	// ある状態において指定されたボタンが押されているかどうかを判断
	bool IsButtonDown(const GamepadState& state, Button button) const;


	// スティックの値の調整
	void AdjustThumb();

	// スティックの各軸の値の調整
	void AdjustThumb(SHORT* thumb);

	// スティックの値の正規化
	float NormalizeThumb(SHORT thumb) const;


	// トリガーの値の調整
	void AdjustTrigger();

	// トリガーの値の正規化
	float NormalizeTrigger(BYTE trigger) const;



	// 非実装 --------------------------------------------------
private:
	// コピーコンストラクタ
	Gamepad(const Gamepad&) = delete;

	// ムーブコンストラクタ
	Gamepad(Gamepad&&) = delete;

	// 代入演算子
	Gamepad& operator=(const Gamepad&) = delete;

	// ムーブ代入演算子
	Gamepad& operator=(Gamepad&&) = delete;
};