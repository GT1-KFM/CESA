// test 16/05/10
// part2
// ���d�C���N���[�h�h�~ ====================================================
#pragma once

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include <Windows.h>

// �N���X��` ==============================================================
	// �E�B���h�E�N���X
	class Window final
	{
		// �����o�ϐ� ----------------------------------------------
		private:
			HWND m_handle;         // �E�B���h�E�n���h��
			MSG  m_messageInfo;    // ���b�Z�[�W���

		// �R���X�g���N�^ ------------------------------------------
		private:
			Window();

		// �f�X�g���N�^ --------------------------------------------
		public:
			~Window() = default;

		// ���� ----------------------------------------------------
		public:
			// �E�B���h�E�n���h���̎擾
			HWND GetHandle() const;

			// �I���R�[�h�̎擾
			int GetExitValue() const;

		// ���� ----------------------------------------------------
		public:
			// ���b�Z�[�W�̏���
			bool HandleMessage();

		// �������� ------------------------------------------------
		private:
			// ������
			HRESULT Initialize(LPCWSTR title, int width, int height);

		// �N���X���� ----------------------------------------------
		public:
			// �t�@�N�g�����\�b�h
			static Window* Create(LPCWSTR title, int width, int height);
	
			// �E�B���h�E�E�v���V�[�W��
			static LRESULT CALLBACK Procedure(HWND hWindow, UINT uMessage, WPARAM wParam, LPARAM lParam);
	};