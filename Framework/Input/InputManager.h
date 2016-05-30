////////////////////////////////////////////////////////////////////////////
//! @file   InputManager.h
//!
//! @brief  ���̓}�l�[�W���̃w�b�_�t�@�C��
//!
//! @date   2016/05/25
//!
//! @author �ߓ��@�D�a
////////////////////////////////////////////////////////////////////////////


// ���d�C���N���[�h�h�~ ====================================================
#pragma once




// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include <memory>

#include <Windows.h>

#include "..\Input\Keyboard.h"
#include "..\Input\Mouse.h"
#include "..\Input\Gamepad.h"
#include "..\System\Window\Window.h"




// ���C�u�����̒ǉ� -------------------------------------------------------
//#pragma comment(lib, "Xinput9_1_0b.lib")    // Xinput�p���C�u����





//------------------------------------------------------------------
//! @brief ���̓f�o�C�X
//------------------------------------------------------------------
enum InputDevice 
{
	KEYBOARD = 0x01,
	MOUSE = 0x02,
	GAMEPAD = 0x04,
};




//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//! @brief ���̓}�l�[�W���N���X
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
class InputManager
{

	struct SetFlag
	{
		bool keyFlag	= false;
		bool mouseFlag	= false;
		bool padFlag	= false;
	};


	// �ÓI�����o�ϐ� ----------------------------------------------
private:

	static InputManager*	   m_pInputManager;	// �C���v�b�g�}�l�[�W���̃|�C���^


	// �����o�ϐ� --------------------------------------------------
private:

	std::unique_ptr<Keyboard>  m_pKeyboard	= nullptr;		// �L�[�{�[�h
	std::unique_ptr<Mouse>     m_pMouse		= nullptr;		// �}�E�X
	std::unique_ptr<Gamepad[]> m_pGamepad	= nullptr;		// �Q�[���p�b�h
	SetFlag					   m_setFlag;


	// �R���X�g���N�^ ----------------------------------------------
private:

	InputManager() = default;



	// �f�X�g���N�^ ------------------------------------------------
public:

	~InputManager() = default;



	// �����o�֐� --------------------------------------------------
public:

	//------------------------------------------------------------------
	//! @brief �L�[�{�[�h���g�p�\�ɂ���
	//------------------------------------------------------------------
	void OnKeyboard()
	{
		m_setFlag.keyFlag = true;
	}




	//------------------------------------------------------------------
	//! @brief �Q�[���p�b�h���g�p�\�ɂ���
	//------------------------------------------------------------------
	void OnGamepad()
	{
		m_setFlag.padFlag = true;
	}





	//------------------------------------------------------------------
	//! @brief �}�E�X���g�p�\�ɂ���
	//------------------------------------------------------------------
	void OnMouse()
	{
		m_setFlag.mouseFlag = true;
	}






	//------------------------------------------------------------------
	//! @brief �L�[�{�[�h�̎擾
	//!
	//! @return �L�[�{�[�h
	//------------------------------------------------------------------
	Keyboard* GetKeyboard() const
	{
		return m_pKeyboard.get();
	}



	//------------------------------------------------------------------
	//! @brief �}�E�X�̎擾
	//!
	//! @return �}�E�X
	//------------------------------------------------------------------
	Mouse* InputManager::GetMouse() const
	{
		return m_pMouse.get();
	}



	//------------------------------------------------------------------
	//! @brief		�Q�[���p�b�h�̎擾
	//!
	//! @param[in]	index �Q�[���p�b�h�̃C���f�b�N�X
	//!
	//! @return		�w��̃Q�[���p�b�h
	//------------------------------------------------------------------
	Gamepad* InputManager::GetGamepad(int index) const
	{
		return &m_pGamepad[index];
	}




	//------------------------------------------------------------------
	//! @brief		���̓f�o�C�X�̏�Ԃ̍X�V
	//------------------------------------------------------------------
	void InputManager::Update()
	{
		// �L�[�{�[�h�̍X�V
		if (m_setFlag.keyFlag)
		{
			m_pKeyboard->Update();
		}


		// �}�E�X�̍X�V
		if (m_setFlag.mouseFlag)
		{
			m_pMouse->Update();
		}


		// �Q�[���p�b�h�̍X�V
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
	//! @brief		������
	//------------------------------------------------------------------
	void Initialize()
	{
		// �L�[�{�[�h�̐���
		m_pKeyboard = std::make_unique<Keyboard>();

		// �}�E�X�̐���
		m_pMouse = std::make_unique<Mouse>(Window::GetInstance()->GetHandle());

		// �Q�[���p�b�h�̐���
		m_pGamepad = std::make_unique<Gamepad[]>(XUSER_MAX_COUNT);
	}



	// �ÓI�����o�֐� --------------------------------------------------
public:


	//-------------------------------------------------------------------------
	//! @brief		���̓}�l�[�W���̃|�C���^�𓾂�
	//!
	//! @param		�Ȃ�
	//!
	//! @retval		pInputManager
	//-------------------------------------------------------------------------
	static InputManager* GetInstance()
	{
		// ���̓}�l�[�W������̏ꍇ����
		if (m_pInputManager == nullptr)
			InputManager::Create();
		return m_pInputManager;
	}



private:

	//-------------------------------------------------------------------------
	//! @brief		���̓}�l�[�W���𐶐�	
	//-------------------------------------------------------------------------
	static void Create()
	{
		m_pInputManager = new InputManager;

		m_pInputManager->Initialize();
	}


public:

	// -------------------------------------------------------------------------
	//! @brief      �I�u�W�F�N�g�̔j��
	// -------------------------------------------------------------------------
	static void Dispose()
	{
		// ��łȂ��ꍇ�j������
		if (m_pInputManager != nullptr)
			delete m_pInputManager;
	}

};