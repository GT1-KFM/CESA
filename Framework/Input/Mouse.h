//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Mouse.h
//!
//! @brief  マウスクラスのヘッダファイル
//!
//! @date   2014/10/10
//!
//! @author 高木 晋
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// 多重インクルード防止 ====================================================
#pragma once




// ヘッダファイルの読み込み ================================================
#include <Windows.h>




// クラス定義 ==============================================================
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//! @brief マウスクラス
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
class Mouse final
{
	// クラス内定数 --------------------------------------------
public:
	//! @brief 仮想ボタンコード
	enum Button : BYTE
	{
		LEFT = VK_LBUTTON,
		RIGHT = VK_RBUTTON,
		WHEEL = VK_MBUTTON,
	};



	// クラス内クラス ------------------------------------------
private:
	//! @brief マウス状態クラス
	struct MouseState
	{
		BYTE  buttonState;        //!< ボタンの状態
		int   wheelDelta;         //!< ホイールの回転量
		POINT pointerPosition;    //!< マウスポインターの座標
	};



	// メンバ変数 ----------------------------------------------
private:
	MouseState m_lastState;       //!< 前回のマウスの状態
	MouseState m_currentState;    //!< 現在のマウスの状態

	int m_wheelDelta;    //!< ホイールの回転量

	HWND m_hWindow;    //!< ウィンドウハンドル



					   // コンストラクタ ------------------------------------------
public:
	explicit Mouse(HWND hWindow);



	// デストラクタ --------------------------------------------
public:
	~Mouse();



	// 属性 ----------------------------------------------------
public:
	// 指定されたボタンが押されているかどうかを判断
	bool IsButtonDown(Button button) const;

	// 指定されたボタンが押されていないかどうかを判断
	bool IsButtonUp(Button button) const;

	// 指定されたボタンが押されたかどうかを判断
	bool IsButtonPressed(Button button) const;

	// 指定されたボタンが離されたかどうかを判断
	bool IsButtonReleased(Button button) const;


	// ホイールの回転量の取得
	int GetWheelDelta() const;


	// マウスポインタの座標の取得
	POINT GetPointerPosition() const;

	// マウスポインタのX座標の取得
	LONG GetPointerPositionX() const;

	// マウスポインタのY座標の取得
	LONG GetPointerPositionY() const;



	// 操作 ----------------------------------------------------
public:
	// マウスの状態の更新
	void Update();



	// 内部実装 ------------------------------------------------
private:
	// ホイールの状態の更新
	void UpdateWheel(int delta);

	// ある状態において指定されたボタンが押されているかどうかを判断
	bool IsButtonDown(const MouseState& mouseState, Button button) const;



	// クラス実装 ----------------------------------------------
private:
	// マウス・プロシージャ
	static LRESULT CALLBACK Procedure(HWND hWindow, UINT uMessage, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);



	// 非実装 --------------------------------------------------
private:
	// コピーコンストラクタ
	Mouse(const Mouse&) = delete;

	// ムーブコンストラクタ
	Mouse(Mouse&&) = delete;

	// 代入演算子
	Mouse& operator=(const Mouse&) = delete;

	// ムーブ代入演算子
	Mouse& operator=(Mouse&&) = delete;
};