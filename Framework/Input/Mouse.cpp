//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Mouse.h
//!
//! @brief  �}�E�X�N���X�̃\�[�X�t�@�C��
//!
//! @date   2014/10/10
//!
//! @author ���� �W
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "Mouse.h"

#include <commctrl.h>




// ���C�u�����̒ǉ� ========================================================
#pragma comment(lib, "comctl32.lib")    // �R�����R���g���[���p���C�u����




// �����o�֐��̒�` ========================================================
//------------------------------------------------------------------
//! @brief �R���X�g���N�^
//!
//! @param �Ȃ�
//------------------------------------------------------------------
Mouse::Mouse(HWND hWindow)
	: m_hWindow(hWindow)
	, m_lastState({ 0, 0,{ 0, 0 } })
	, m_currentState({ 0, 0,{ 0, 0 } })
{
	// �E�B���h�E�̃T�u�N���X��
	UINT_PTR  subclassID = reinterpret_cast<DWORD_PTR>(this);
	DWORD_PTR referenceData = reinterpret_cast<DWORD_PTR>(this);
	SetWindowSubclass(hWindow, Procedure, subclassID, referenceData);
}



//------------------------------------------------------------------
//! @brief �f�X�g���N�^
//------------------------------------------------------------------
Mouse::~Mouse()
{
	// �E�B���h�E�̃T�u�N���X���̉���
	UINT_PTR subclassID = reinterpret_cast<DWORD_PTR>(this);
	RemoveWindowSubclass(m_hWindow, Procedure, subclassID);
}



//------------------------------------------------------------------
//! @brief �w�肳�ꂽ�{�^����������Ă��邩�ǂ����𔻒f
//!
//! @param[in] button ���肵�����{�^���̉��z�{�^���R�[�h
//!
//! @retval true  �w�肳�ꂽ�{�^����������Ă���ꍇ
//! @retval false ����ȊO�̏ꍇ
//------------------------------------------------------------------
bool Mouse::IsButtonDown(Button button) const
{
	return IsButtonDown(m_currentState, button);
}



//------------------------------------------------------------------
//! @brief �w�肳�ꂽ�{�^����������Ă��Ȃ����ǂ����𔻒f
//!
//! @param[in] button ���肵�����{�^���̉��z�{�^���R�[�h
//!
//! @retval true  �w�肳�ꂽ�{�^����������Ă��Ȃ��ꍇ
//! @retval false ����ȊO�̏ꍇ
//------------------------------------------------------------------
bool Mouse::IsButtonUp(Button button) const
{
	return !IsButtonDown(m_currentState, button);
}



//------------------------------------------------------------------
//! @brief �w�肳�ꂽ�{�^���������ꂽ���ǂ����𔻒f
//!
//! @param[in] button ���肵�����{�^���̉��z�{�^���R�[�h
//!
//! @retval true  �w�肳�ꂽ�{�^���������ꂽ�ꍇ
//! @retval false ����ȊO�̏ꍇ
//------------------------------------------------------------------
bool Mouse::IsButtonPressed(Button button) const
{
	return IsButtonDown(m_currentState, button) && !IsButtonDown(m_lastState, button);
}



//------------------------------------------------------------------
//! @brief �w�肳�ꂽ�{�^���������ꂽ���ǂ����𔻒f
//!
//! @param[in] button ���肵�����{�^���̉��z�{�^���R�[�h
//!
//! @retval true  �w�肳�ꂽ�{�^���������ꂽ�ꍇ
//! @retval false ����ȊO�̏ꍇ
//------------------------------------------------------------------
bool Mouse::IsButtonReleased(Button button) const
{
	return !IsButtonDown(m_currentState, button) && IsButtonDown(m_lastState, button);
}



//------------------------------------------------------------------
//! @brief �z�C�[���̉�]��(�m�b�`)�̎擾
//!
//! @param �Ȃ�
//!
//! @return �z�C�[���̉�]��(�m�b�`)
//------------------------------------------------------------------
int Mouse::GetWheelDelta() const
{
	return m_currentState.wheelDelta / WHEEL_DELTA;
}



//------------------------------------------------------------------
//! @brief �}�E�X�|�C���^�̍��W�̎擾
//!
//! @param �Ȃ�
//!
//! @return �}�E�X�|�C���^�̍��W
//------------------------------------------------------------------
POINT Mouse::GetPointerPosition() const
{
	return m_currentState.pointerPosition;
}



//------------------------------------------------------------------
//! @brief �}�E�X�|�C���^��X���W�̎擾
//!
//! @param �Ȃ�
//!
//! @return �}�E�X�|�C���^��X���W
//------------------------------------------------------------------
LONG Mouse::GetPointerPositionX() const
{
	return m_currentState.pointerPosition.x;
}



//------------------------------------------------------------------
//! @brief �}�E�X�|�C���^��Y���W�̎擾
//!
//! @param �Ȃ�
//!
//! @return �}�E�X�|�C���^��Y���W
//------------------------------------------------------------------
LONG Mouse::GetPointerPositionY() const
{
	return m_currentState.pointerPosition.y;
}



//------------------------------------------------------------------
//! @brief �}�E�X�̏�Ԃ̍X�V
//!
//! @param �Ȃ�
//!
//! @return �Ȃ�
//------------------------------------------------------------------
void Mouse::Update()
{
	// ��Ԃ̗�����ۑ�
	m_lastState = m_currentState;

	// �{�^���̌��݂̏�Ԃ��擾
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


	// �z�C�[���̉�]�ʂ̎擾
	m_currentState.wheelDelta = m_wheelDelta;
	m_wheelDelta = 0;


	// �}�E�X�|�C���^�[�̍��W�̎擾
	GetCursorPos(&m_currentState.pointerPosition);
	ScreenToClient(m_hWindow, &m_currentState.pointerPosition);
}



//------------------------------------------------------------------
//! @brief �z�C�[���̏�Ԃ̍X�V
//!
//! @param[in] wheelDelta �z�C�[���̉�]��
//!
//! @return �Ȃ�
//------------------------------------------------------------------
void Mouse::UpdateWheel(int wheelDelta)
{
	m_wheelDelta += wheelDelta;
}



//------------------------------------------------------------------
//! @brief �����Ԃɂ����Ďw�肳�ꂽ�{�^����������Ă��邩�ǂ����𔻒f
//!
//! @param[in] mouseState �}�E�X�̏��
//! @param[in] button     ���肵�����{�^���̉��z�L�[�R�[�h
//!
//! @retval true  �w�肳�ꂽ�{�^����������Ă���ꍇ
//! @retval false ����ȊO�̏ꍇ
//------------------------------------------------------------------
inline bool Mouse::IsButtonDown(const MouseState& mouseState, Button button) const
{
	return (mouseState.buttonState & button) ? true : false;
}




// �ÓI�����o�֐��̒�` ====================================================
//------------------------------------------------------------------
//! @brief �}�E�X�E�v���V�[�W��
//!
//! @param[in] hWindow     �E�B���h�E�n���h��
//! @param[in] uMessage    ���b�Z�[�W�̎��ʎq
//! @param[in] wParam      ���b�Z�[�W��1�Ԗڂ̃p�����[�^
//! @param[in] lParam      ���b�Z�[�W��2�Ԗڂ̃p�����[�^
//! @param[in] uIdSubclass �T�u�N���XID
//! @param[in] dwRefData   �Q�ƃf�[�^
//!
//! @return ���b�Z�[�W�����̌���(���M���ꂽ���b�Z�[�W�ɂ���ĈقȂ�)
//------------------------------------------------------------------
LRESULT CALLBACK Mouse::Procedure(HWND hWindow, UINT uMessage, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
	// ���b�Z�[�W�̏���
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

	// �����ŏ������Ȃ����b�Z�[�W��Windows�ɔC����
	return DefSubclassProc(hWindow, uMessage, wParam, lParam);
}