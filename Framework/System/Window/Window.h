///////////////////////////////////////////////////////////////////////////////////
//! @file   Window.h
//!
//! @brief  �E�B���h�E�N���X�̃w�b�_�t�@�C��
//!
//! @date   2016/5/18
//!
//! @author �ߓ��D�a
/////////////////////////////////////////////////////////////////////////////////

// ���d�C���N���[�h�h�~ 
#pragma once




// �w�b�_�t�@�C���̓ǂݍ���
#include <Windows.h>




// ---------------------------------------------------------------------------
// Window�N���X
// ---------------------------------------------------------------------------
class Window 
{

	// �ÓI�����o�ϐ� --------------------------------------------------------
public:
	static const int WINDOW_WIDTH  = 1280;		// �E�B���h�E��
	static const int WINDOW_HEIGHT = 720;		// �E�B���h�E����
	static Window*		m_pWindow;              // �E�B���h�E�̃A�h���X

	


	// �����o�ϐ� -------------------------------------------------------------
private:
	HWND				m_handle;				// �E�B���h�E�n���h��
	MSG					m_messageInfo;			// ���b�Z�[�W���
	int					m_screenWidth;			// �E�B���h�E��
	int					m_screenHeight;			// �E�B���h�E����

	// �R���X�g���N�^ ---------------------------------------------------------
private:
	Window() = default;



	// �f�X�g���N�^ -----------------------------------------------------------
public:
	~Window() = default;



	// �ÓI�����o�֐� ---------------------------------------------------------
public:


	// ------------------------------------------------------------------------
	//! @brief      Window�I�u�W�F�N�g�ւ̃A�h���X���擾����
	//!
	//! @return     pWindow
	// ------------------------------------------------------------------------
	static Window* GetInstance()
	{
		// Window�𐶐�����
		if (m_pWindow == nullptr)
		{
			m_pWindow = Window::Create();
		}

		return m_pWindow;
	}




	
private:

	// ------------------------------------------------------------------------
	//! @brief      �E�B���h�E�I�u�W�F�N�g�̐���
	//!
	//! @return     pWindow	�����ɐ���
	//! @return		nullptr	�����Ɏ��s
	// ------------------------------------------------------------------------
	static Window* Create()
	{
		// �E�C���h�E�I�u�W�F�N�g�̐���
		Window* pWindow = new Window();

		if (!pWindow)
		{
			return nullptr;
		}


		// ������
		if (FAILED(pWindow->Initialize()))
		{
			delete pWindow;
			return nullptr;
		}


		// �E�B���h�E�I�u�W�F�N�g�̐����ɐ���
		return pWindow;
	}


	// ------------------------------------------------------------------------
	//! @brief      �E�B���h�E�v���V�[�W��
	//!
	//! @param[in]	hWindow	 �E�B���h�E�n���h��
	//! @param[in]	uMessage ���b�Z�[�W�̎w��
	//! @param[in]	wParam	 ���b�Z�[�W�̈�Ԗڂ̃p�����[�^
	//! @param[in]	lParam	 ���b�Z�[�W�̓�Ԗڂ̃p�����[�^
	//!
	//! @return     0		�I���v��
	//! @return     LRESULT	windows���b�Z�[�W�̌���
	// ------------------------------------------------------------------------
	static LRESULT CALLBACK Procedure(HWND hWindow, UINT uMessage, WPARAM wParam, LPARAM lParam)
	{
		// ���b�Z�[�W�̏���
		switch (uMessage)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

		case WM_KEYDOWN:
			if (wParam == VK_ESCAPE)
			{
				PostQuitMessage(0);
				return 0;
			}
			break;
		}

		// �����ŏ������Ȃ����b�Z�[�W��Windows�ɔC����
		return DefWindowProc(hWindow, uMessage, wParam, lParam);
	}


	// �����o�֐� -------------------------------------------------------------
public:

	// ------------------------------------------------------------------------
	//! @brief      �E�B���h�E�n���h���̎擾
	//!
	//! @return     handle(HWND)
	// ------------------------------------------------------------------------
	HWND GetHandle() const
	{
		return m_handle;
	}




	// ------------------------------------------------------------------------
	//! @brief     �I���R�[�h�̎擾 
	//!
	//! @return     wPaaram(int)
	// ------------------------------------------------------------------------
	int GetExitValue() const
	{
		return m_messageInfo.wParam;
	}




	// ------------------------------------------------------------------------
	//! @brief    �Q�[����ʂ̕����擾
	//!
	//! @return     wPaaram(int)
	// ------------------------------------------------------------------------
	int GetScreenWidth()
	{
		return m_screenWidth;
	}




	// ------------------------------------------------------------------------
	//! @brief     �Q�[����ʂ̍������擾 
	//!
	//! @return     wPaaram(int)
	// ------------------------------------------------------------------------
	int GetScreenHeight()
	{
		return m_screenHeight;
	}




public:

	// ------------------------------------------------------------------------
	//! @brief      ���b�Z�[�W�̏���
	//!
	//! @return     false	�E�B���h�E�̏I��
	//! @return		true	�E�B���h�E�̑��s
	// ------------------------------------------------------------------------
	bool HandleMessage()
	{
		// �|�X�g�ς݃��b�Z�[�W�̏���
		while (PeekMessage(&m_messageInfo, NULL, 0, 0, PM_REMOVE))
		{
			// WM_QUIT���b�Z�[�W�̏���
			if (m_messageInfo.message == WM_QUIT)
			{
				return false;
			}

			// WM_QUIT�ȊO�̃��b�Z�[�W�̏���
			TranslateMessage(&m_messageInfo);
			DispatchMessage(&m_messageInfo);
		}

		return true;
	}




private:

	// ------------------------------------------------------------------------
	//! @brief      ������
	//!
	//! @return     E_FAIL	���������s
	//! @return		S_OK    ����������
	// ------------------------------------------------------------------------
	HRESULT Initialize()
	{
		// �N���X�l�[��
		LPCWSTR CLASS_NAME = L"GameWindowClass";
		// �^�C�g���l�[��
		LPCWSTR TITLE_NAME = L"Picker";
		// ���W���[���n���h���𓾂�
		HINSTANCE hInstance = GetModuleHandle(nullptr);


		// �E�B���h�E�E�N���X��o�^
		WNDCLASSEX windowClass;
		ZeroMemory(&windowClass, sizeof(windowClass));

		windowClass.cbSize = sizeof(WNDCLASSEX);
		windowClass.style = CS_HREDRAW | CS_VREDRAW;
		windowClass.lpfnWndProc = Window::Procedure;
		windowClass.cbClsExtra = 0;
		windowClass.cbWndExtra = 0;
		windowClass.hInstance = hInstance;
		windowClass.hIcon = LoadIcon(hInstance, L"ICON");
		windowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
		windowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		windowClass.lpszMenuName = nullptr;
		windowClass.lpszClassName = CLASS_NAME;
		windowClass.hIconSm = LoadIcon(hInstance, L"ICON");

		if (!RegisterClassEx(&windowClass))
		{
			// �������Ɏ��s
			return E_FAIL;
		}


		// �E�B���h�E�X�^�C���̐ݒ�
		DWORD windowStyle = WS_OVERLAPPEDWINDOW    // ��{�X�^�C��(�I�[�o�[���b�v�E�B���h�E)
			& ~WS_MAXIMIZEBOX        // �ő剻�{�^���̖�����
			& ~WS_THICKFRAME;        // �E�B���h�E�̃T�C�Y�ύX�̖�����


		// �E�B���h�E�T�C�Y�̎Z�o
		RECT rect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
		AdjustWindowRect(&rect, windowStyle, FALSE);

		m_screenWidth = rect.right - rect.left;
		m_screenHeight = rect.bottom - rect.top;


		// �E�B���h�E�̍쐬
		m_handle = CreateWindow(
			CLASS_NAME,
			TITLE_NAME,
			windowStyle,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			m_screenWidth,
			m_screenHeight,
			nullptr,
			nullptr,
			windowClass.hInstance,
			NULL
			);

		if (!m_handle)
		{
			// �������Ɏ��s
			return E_FAIL;
		}


		// �E�B���h�E�̕\��
		ShowWindow(m_handle, SW_SHOWNORMAL);


		// �������ɐ���
		return S_OK;
	}





};