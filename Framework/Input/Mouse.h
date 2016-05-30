//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Mouse.h
//!
//! @brief  �}�E�X�N���X�̃w�b�_�t�@�C��
//!
//! @date   2014/10/10
//!
//! @author ���� �W
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// ���d�C���N���[�h�h�~ ====================================================
#pragma once




// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include <Windows.h>




// �N���X��` ==============================================================
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//! @brief �}�E�X�N���X
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
class Mouse final
{
	// �N���X���萔 --------------------------------------------
public:
	//! @brief ���z�{�^���R�[�h
	enum Button : BYTE
	{
		LEFT = VK_LBUTTON,
		RIGHT = VK_RBUTTON,
		WHEEL = VK_MBUTTON,
	};



	// �N���X���N���X ------------------------------------------
private:
	//! @brief �}�E�X��ԃN���X
	struct MouseState
	{
		BYTE  buttonState;        //!< �{�^���̏��
		int   wheelDelta;         //!< �z�C�[���̉�]��
		POINT pointerPosition;    //!< �}�E�X�|�C���^�[�̍��W
	};



	// �����o�ϐ� ----------------------------------------------
private:
	MouseState m_lastState;       //!< �O��̃}�E�X�̏��
	MouseState m_currentState;    //!< ���݂̃}�E�X�̏��

	int m_wheelDelta;    //!< �z�C�[���̉�]��

	HWND m_hWindow;    //!< �E�B���h�E�n���h��



					   // �R���X�g���N�^ ------------------------------------------
public:
	explicit Mouse(HWND hWindow);



	// �f�X�g���N�^ --------------------------------------------
public:
	~Mouse();



	// ���� ----------------------------------------------------
public:
	// �w�肳�ꂽ�{�^����������Ă��邩�ǂ����𔻒f
	bool IsButtonDown(Button button) const;

	// �w�肳�ꂽ�{�^����������Ă��Ȃ����ǂ����𔻒f
	bool IsButtonUp(Button button) const;

	// �w�肳�ꂽ�{�^���������ꂽ���ǂ����𔻒f
	bool IsButtonPressed(Button button) const;

	// �w�肳�ꂽ�{�^���������ꂽ���ǂ����𔻒f
	bool IsButtonReleased(Button button) const;


	// �z�C�[���̉�]�ʂ̎擾
	int GetWheelDelta() const;


	// �}�E�X�|�C���^�̍��W�̎擾
	POINT GetPointerPosition() const;

	// �}�E�X�|�C���^��X���W�̎擾
	LONG GetPointerPositionX() const;

	// �}�E�X�|�C���^��Y���W�̎擾
	LONG GetPointerPositionY() const;



	// ���� ----------------------------------------------------
public:
	// �}�E�X�̏�Ԃ̍X�V
	void Update();



	// �������� ------------------------------------------------
private:
	// �z�C�[���̏�Ԃ̍X�V
	void UpdateWheel(int delta);

	// �����Ԃɂ����Ďw�肳�ꂽ�{�^����������Ă��邩�ǂ����𔻒f
	bool IsButtonDown(const MouseState& mouseState, Button button) const;



	// �N���X���� ----------------------------------------------
private:
	// �}�E�X�E�v���V�[�W��
	static LRESULT CALLBACK Procedure(HWND hWindow, UINT uMessage, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);



	// ����� --------------------------------------------------
private:
	// �R�s�[�R���X�g���N�^
	Mouse(const Mouse&) = delete;

	// ���[�u�R���X�g���N�^
	Mouse(Mouse&&) = delete;

	// ������Z�q
	Mouse& operator=(const Mouse&) = delete;

	// ���[�u������Z�q
	Mouse& operator=(Mouse&&) = delete;
};