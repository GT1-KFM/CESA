//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Gamepad.h
//!
//! @brief  �Q�[���p�b�h(Xbox 360 �R���g���[���[)�N���X�̃w�b�_�t�@�C��
//!
//! @date   2014/10/10
//!
//! @author ���� �W
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// ���d�C���N���[�h�h�~ ====================================================
#pragma once




// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include <Windows.h>
#include <Xinput.h>




// �N���X��` ==============================================================
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//! @brief �Q�[���p�b�h(Xbox 360 �R���g���[���[)�N���X
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
class Gamepad
{
	// �N���X���萔 --------------------------------------------
public:
	//! @brief ���z�{�^���R�[�h
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

	static const int TRIGGER_MAX = 255;    //!< �g���K�[�̍ő�l
	static const int THUMB_LIMIT = 32767;    //!< �X�e�B�b�N�̏㉺��(�})



											 // �N���X���N���X ------------------------------------------
private:
	//! @brief �Q�[���p�b�h��ԃN���X
	struct GamepadState
	{
		bool         isConnected;    //!< �ڑ��̗L��
		XINPUT_STATE state;          //!< �Q�[���p�b�h�̏��
	};



	// �����o�ϐ� ----------------------------------------------
private:
	DWORD m_userIndex;    //!< ���[�U�[�̃Q�[���p�b�h�̃C���f�b�N�X

	GamepadState m_lastState;       //!< �O��̃Q�[���p�b�h�̏��
	GamepadState m_currentState;    //!< ���݂̃Q�[���p�b�h�̏��



									// �R���X�g���N�^ ------------------------------------------
public:
	explicit Gamepad(DWORD userIndex = 0);



	// �f�X�g���N�^ --------------------------------------------
public:
	~Gamepad() = default;



	// ���� ----------------------------------------------------
public:
	// �Q�[���p�b�h���ڑ�����Ă��邩�ǂ����𔻒f
	bool IsConnected() const;


	// �w�肳�ꂽ�{�^����������Ă��邩�ǂ����𔻒f
	bool IsButtonDown(Button button) const;

	// �w�肳�ꂽ�{�^����������Ă��Ȃ����ǂ����𔻒f
	bool IsButtonUp(Button button) const;

	// �w�肳�ꂽ�{�^���������ꂽ���ǂ����𔻒f
	bool IsButtonPressed(Button button) const;

	// �w�肳�ꂽ�{�^���������ꂽ���ǂ����𔻒f
	bool IsButtonReleased(Button button) const;


	// ���X�e�B�b�N��X���̒l�̎擾
	float GetLeftThumbX() const;

	// ���X�e�B�b�N��Y���̒l�̎擾
	float GetLeftThumbY() const;

	// �E�X�e�B�b�N��X���̒l�̎擾
	float GetRightThumbX() const;

	// �E�X�e�B�b�N��Y���̒l�̎擾
	float GetRightThumbY() const;


	// ���g���K�[�̒l�̎擾
	float GetLeftTrigger() const;

	// �E�g���K�[�̒l�̎擾
	float GetRightTrigger() const;



	// ���� ----------------------------------------------------
public:
	// �Q�[���p�b�h�̏�Ԃ̍X�V
	void Update();



	// �������� ------------------------------------------------
private:
	// �����Ԃɂ����Ďw�肳�ꂽ�{�^����������Ă��邩�ǂ����𔻒f
	bool IsButtonDown(const GamepadState& state, Button button) const;


	// �X�e�B�b�N�̒l�̒���
	void AdjustThumb();

	// �X�e�B�b�N�̊e���̒l�̒���
	void AdjustThumb(SHORT* thumb);

	// �X�e�B�b�N�̒l�̐��K��
	float NormalizeThumb(SHORT thumb) const;


	// �g���K�[�̒l�̒���
	void AdjustTrigger();

	// �g���K�[�̒l�̐��K��
	float NormalizeTrigger(BYTE trigger) const;



	// ����� --------------------------------------------------
private:
	// �R�s�[�R���X�g���N�^
	Gamepad(const Gamepad&) = delete;

	// ���[�u�R���X�g���N�^
	Gamepad(Gamepad&&) = delete;

	// ������Z�q
	Gamepad& operator=(const Gamepad&) = delete;

	// ���[�u������Z�q
	Gamepad& operator=(Gamepad&&) = delete;
};