////////////////////////////////////////////////////////////////////////////
//! @file   InputManager.h
//!
//! @brief  入力マネージャのヘッダファイル
//!
//! @date   2016/05/25
//!
//! @author 近藤　優和
////////////////////////////////////////////////////////////////////////////


// 多重インクルード防止 ====================================================
#pragma once




// ヘッダファイルの読み込み ================================================
#include <memory>

#include <Windows.h>

#include "..\Input\Keyboard.h"
#include "..\Input\Mouse.h"
#include "..\Input\Gamepad.h"
#include "..\System\Window\Window.h"




// ライブラリの追加 -------------------------------------------------------
//#pragma comment(lib, "Xinput9_1_0b.lib")    // Xinput用ライブラリ





//------------------------------------------------------------------
//! @brief 入力デバイス
//------------------------------------------------------------------
enum InputDevice 
{
	KEYBOARD = 0x01,
	MOUSE = 0x02,
	GAMEPAD = 0x04,
};




//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//! @brief 入力マネージャクラス
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
class InputManager
{

	struct SetFlag
	{
		bool keyFlag	= false;
		bool mouseFlag	= false;
		bool padFlag	= false;
	};


	// 静的メンバ変数 ----------------------------------------------
private:

	static InputManager*	   m_pInputManager;	// インプットマネージャのポインタ


	// メンバ変数 --------------------------------------------------
private:

	std::unique_ptr<Keyboard>  m_pKeyboard	= nullptr;		// キーボード
	std::unique_ptr<Mouse>     m_pMouse		= nullptr;		// マウス
	std::unique_ptr<Gamepad[]> m_pGamepad	= nullptr;		// ゲームパッド
	SetFlag					   m_setFlag;


	// コンストラクタ ----------------------------------------------
private:

	InputManager() = default;



	// デストラクタ ------------------------------------------------
public:

	~InputManager() = default;



	// メンバ関数 --------------------------------------------------
public:

	//------------------------------------------------------------------
	//! @brief キーボードを使用可能にする
	//------------------------------------------------------------------
	void OnKeyboard()
	{
		m_setFlag.keyFlag = true;
	}




	//------------------------------------------------------------------
	//! @brief ゲームパッドを使用可能にする
	//------------------------------------------------------------------
	void OnGamepad()
	{
		m_setFlag.padFlag = true;
	}





	//------------------------------------------------------------------
	//! @brief マウスを使用可能にする
	//------------------------------------------------------------------
	void OnMouse()
	{
		m_setFlag.mouseFlag = true;
	}






	//------------------------------------------------------------------
	//! @brief キーボードの取得
	//!
	//! @return キーボード
	//------------------------------------------------------------------
	Keyboard* GetKeyboard() const
	{
		return m_pKeyboard.get();
	}



	//------------------------------------------------------------------
	//! @brief マウスの取得
	//!
	//! @return マウス
	//------------------------------------------------------------------
	Mouse* InputManager::GetMouse() const
	{
		return m_pMouse.get();
	}



	//------------------------------------------------------------------
	//! @brief		ゲームパッドの取得
	//!
	//! @param[in]	index ゲームパッドのインデックス
	//!
	//! @return		指定のゲームパッド
	//------------------------------------------------------------------
	Gamepad* InputManager::GetGamepad(int index) const
	{
		return &m_pGamepad[index];
	}




	//------------------------------------------------------------------
	//! @brief		入力デバイスの状態の更新
	//------------------------------------------------------------------
	void InputManager::Update()
	{
		// キーボードの更新
		if (m_setFlag.keyFlag)
		{
			m_pKeyboard->Update();
		}


		// マウスの更新
		if (m_setFlag.mouseFlag)
		{
			m_pMouse->Update();
		}


		// ゲームパッドの更新
		if (m_setFlag.padFlag)
		{
			for (int i = 0; i < XUSER_MAX_COUNT; i++)
			{
				m_pGamepad[i].Update();
			}
		}
	}

private:

	//------------------------------------------------------------------
	//! @brief		初期化
	//------------------------------------------------------------------
	void Initialize()
	{
		// キーボードの生成
		m_pKeyboard = std::make_unique<Keyboard>();

		// マウスの生成
		m_pMouse = std::make_unique<Mouse>(Window::GetInstance()->GetHandle());

		// ゲームパッドの生成
		m_pGamepad = std::make_unique<Gamepad[]>(XUSER_MAX_COUNT);
	}



	// 静的メンバ関数 --------------------------------------------------
public:


	//-------------------------------------------------------------------------
	//! @brief		入力マネージャのポインタを得る
	//!
	//! @param		なし
	//!
	//! @retval		pInputManager
	//-------------------------------------------------------------------------
	static InputManager* GetInstance()
	{
		// 入力マネージャが空の場合生成
		if (m_pInputManager == nullptr)
			InputManager::Create();
		return m_pInputManager;
	}



private:

	//-------------------------------------------------------------------------
	//! @brief		入力マネージャを生成	
	//-------------------------------------------------------------------------
	static void Create()
	{
		m_pInputManager = new InputManager;

		m_pInputManager->Initialize();
	}


public:

	// -------------------------------------------------------------------------
	//! @brief      オブジェクトの破棄
	// -------------------------------------------------------------------------
	static void Dispose()
	{
		// 空でない場合破棄する
		if (m_pInputManager != nullptr)
			delete m_pInputManager;
	}

};