//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Gamepad.h
//!
//! @brief  �Q�[���p�b�h(Xbox 360 �R���g���[���[)�N���X�̃\�[�X�t�@�C��
//!
//! @date   2014/10/10
//!
//! @author ���� �W
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "Gamepad.h"




// ���C�u�����̒ǉ� ========================================================
#pragma comment(lib, "Xinput9_1_0.lib")    // Xinput�p���C�u����




// �����o�֐��̒�` ========================================================
//------------------------------------------------------------------
//! @brief �R���X�g���N�^
//!
//! @param �Ȃ�
//------------------------------------------------------------------
Gamepad::Gamepad(DWORD userIndex)
	: m_userIndex(userIndex)
	, m_lastState({ false,{ 0 } })
	, m_currentState({ false,{ 0 } })
{
}



//------------------------------------------------------------------
//! @brief �Q�[���p�b�h���ڑ�����Ă��邩�ǂ����𔻒f
//!
//! @param �Ȃ�
//!
//! @retval true  �ڑ�����Ă���ꍇ
//! @retval false ����ȊO�̏ꍇ
//------------------------------------------------------------------
bool Gamepad::IsConnected() const
{
	return m_currentState.isConnected;
}



//------------------------------------------------------------------
//! @brief �w�肳�ꂽ�{�^����������Ă��邩�ǂ����𔻒f
//!
//! @param[in] button ���肵�����{�^���̉��z�{�^���R�[�h
//!
//! @retval true  �w�肳�ꂽ�{�^����������Ă���ꍇ
//! @retval false ����ȊO�̏ꍇ
//------------------------------------------------------------------
bool Gamepad::IsButtonDown(Button button) const
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
bool Gamepad::IsButtonUp(Button button) const
{
	return !IsButtonDown(m_currentState, button);
}



//------------------------------------------------------------------
//! @brief �w�肳�ꂽ�{�^���������ꂽ���ǂ����𔻒f
//!
//! @param[in] button ���肵�����{�^���̉��z�{�^���R�[�h
//!
//! @retval true  �w�肳�ꂽ�L�[�������ꂽ�ꍇ
//! @retval false ����ȊO�̏ꍇ
//------------------------------------------------------------------
bool Gamepad::IsButtonPressed(Button button) const
{
	return IsButtonDown(m_currentState, button) && !IsButtonDown(m_lastState, button);
}



//------------------------------------------------------------------
//! @brief �w�肳�ꂽ�{�^���������ꂽ���ǂ����𔻒f
//!
//! @param[in] button ���肵�����{�^���̉��z�{�^���R�[�h
//!
//! @retval true  �w�肳�ꂽ�L�[�������ꂽ�ꍇ
//! @retval false ����ȊO�̏ꍇ
//------------------------------------------------------------------
bool Gamepad::IsButtonReleased(Button button) const
{
	return !IsButtonDown(m_currentState, button) && IsButtonDown(m_lastState, button);
}



//------------------------------------------------------------------
//! @brief ���X�e�B�b�N��X���̒l�̎擾
//!
//! @param �Ȃ�
//!
//! @return ���X�e�B�b�N��X���̒l(-1.0�`1.0)
//------------------------------------------------------------------
float Gamepad::GetLeftThumbX() const
{
	return NormalizeThumb(m_currentState.state.Gamepad.sThumbLX);
}



//------------------------------------------------------------------
//! @brief ���X�e�B�b�N��Y���̒l�̎擾
//!
//! @param �Ȃ�
//!
//! @return ���X�e�B�b�N��Y���̒l(-1.0�`1.0)
//------------------------------------------------------------------
float Gamepad::GetLeftThumbY() const
{
	return NormalizeThumb(m_currentState.state.Gamepad.sThumbLY);
}



//------------------------------------------------------------------
//! @brief �E�X�e�B�b�N��X���̒l�̎擾
//!
//! @param �Ȃ�
//!
//! @return �E�X�e�B�b�N��X���̒l(-1.0�`1.0)
//------------------------------------------------------------------
float Gamepad::GetRightThumbX() const
{
	return NormalizeThumb(m_currentState.state.Gamepad.sThumbRX);
}



//------------------------------------------------------------------
//! @brief �E�X�e�B�b�N��Y���̒l�̎擾
//!
//! @param �Ȃ�
//!
//! @return �E�X�e�B�b�N��Y���̒l(-1.0�`1.0)
//------------------------------------------------------------------
float Gamepad::GetRightThumbY() const
{
	return NormalizeThumb(m_currentState.state.Gamepad.sThumbRY);
}



//------------------------------------------------------------------
//! @brief ���g���K�[�̒l�̎擾
//!
//! @param �Ȃ�
//!
//! @return ���g���K�[�̒l(0.0�`1.0)
//------------------------------------------------------------------
float Gamepad::GetLeftTrigger() const
{
	return NormalizeTrigger(m_currentState.state.Gamepad.bLeftTrigger);
}



//------------------------------------------------------------------
//! @brief �E�g���K�[�̒l�̎擾
//!
//! @param �Ȃ�
//!
//! @return �E�g���K�[�̒l(0.0�`1.0)
//------------------------------------------------------------------
float Gamepad::GetRightTrigger() const
{
	return NormalizeTrigger(m_currentState.state.Gamepad.bRightTrigger);
}



//------------------------------------------------------------------
//! @brief �Q�[���p�b�h�̏�Ԃ̍X�V
//!
//! @param �Ȃ�
//!
//! @return �Ȃ�
//------------------------------------------------------------------
void Gamepad::Update()
{
	// ��Ԃ̗�����ۑ�
	m_lastState = m_currentState;


	// �Q�[���p�b�h�̌��݂̏�Ԃ��擾
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
//! @brief �����Ԃɂ����Ďw�肳�ꂽ�{�^����������Ă��邩�ǂ����𔻒f
//!
//! @param[in] state  �Q�[���p�b�h�̏��
//! @param[in] button ���肵�����{�^���̉��z�{�^���R�[�h
//!
//! @retval true  �w�肳�ꂽ�L�[��������Ă���ꍇ
//! @retval false ����ȊO�̏ꍇ
//------------------------------------------------------------------
inline bool Gamepad::IsButtonDown(const GamepadState& gamepadState, Button button) const
{
	return (gamepadState.state.Gamepad.wButtons & button) ? true : false;
}



//------------------------------------------------------------------
//! @brief �X�e�B�b�N�̒l�̒���
//!
//! @param �Ȃ�
//!
//! @return �Ȃ�
//------------------------------------------------------------------
void Gamepad::AdjustThumb()
{
	// ���X�e�B�b�N�̒l�̒���
	AdjustThumb(&m_currentState.state.Gamepad.sThumbLX);
	AdjustThumb(&m_currentState.state.Gamepad.sThumbLY);


	// �E�X�e�B�b�N�̒l�̒���
	AdjustThumb(&m_currentState.state.Gamepad.sThumbRX);
	AdjustThumb(&m_currentState.state.Gamepad.sThumbRY);
}



//------------------------------------------------------------------
//! @brief �X�e�B�b�N�̊e���̒l�̒���
//!
//! @param[in] thumb �l�𒲐�����X�e�B�b�N�̎�
//!
//! @return �Ȃ�
//------------------------------------------------------------------
void Gamepad::AdjustThumb(SHORT* thumb)
{
	// ���X�e�B�b�N��X���̒l�̒���
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
//! @brief �X�e�B�b�N�̒l�̐��K��
//!
//! @param thumb
//!
//! @return -1.0�`1.0�ɐ��K�������X�e�B�b�N�̒l
//------------------------------------------------------------------
inline float Gamepad::NormalizeThumb(SHORT thumb) const
{
	return thumb / static_cast<float>(THUMB_LIMIT);
}



//------------------------------------------------------------------
//! @brief �g���K�[�̒l�̒���
//!
//! @param �Ȃ�
//!
//! @return �Ȃ�
//------------------------------------------------------------------
void Gamepad::AdjustTrigger()
{
	// ���g���K�[�̒l�̒���
	if (m_currentState.state.Gamepad.bLeftTrigger < XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
	{
		m_currentState.state.Gamepad.bLeftTrigger = 0;
	}


	// �E�g���K�[�̒l�̒���
	if (m_currentState.state.Gamepad.bRightTrigger < XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
	{
		m_currentState.state.Gamepad.bRightTrigger = 0;
	}
}



//------------------------------------------------------------------
//! @brief �g���K�[�̒l�̐��K��
//!
//! @param trigger
//!
//! @return 0.0�`1.0�ɐ��K�������g���K�[�̒l
//------------------------------------------------------------------
inline float Gamepad::NormalizeTrigger(BYTE trigger) const
{
	return trigger / static_cast<float>(TRIGGER_MAX);
}