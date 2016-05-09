//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Window.h
//!
//! @brief  �E�B���h�E�N���X�̃w�b�_�t�@�C��
//!
//! @date   
//!
//! @author 
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// ���d�C���N���[�h�h�~ ====================================================
#pragma once




// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include <Windows.h>




//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//! @brief �E�B���h�E�N���X
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
class Window final
{

	// �萔
public:
	static const int WINDOW_WIDTH = 1280;		// �E�B���h�E��
	static const int WINDOW_HEIGHT = 780;		// �E�B���h�E����


												// �����o�ϐ� ----------------------------------------------
private:
	HWND				m_handle;				// �E�B���h�E�n���h��
	MSG					m_messageInfo;			// ���b�Z�[�W���
	static Window*		m_pWindow;              // �@


												// �R���X�g���N�^ ------------------------------------------
private:
	Window();



	// �f�X�g���N�^ --------------------------------------------
public:
	~Window() = default;



	// ���� ----------------------------------------------------
public:

	// Window�I�u�W�F�N�g�ւ̃A�h���X���擾����
	static Window* GetInstance()
	{
		if (m_pWindow == nullptr)
		{
			m_pWindow = new Window();
		}

		return m_pWindow;
	}


	// �E�B���h�E�n���h���̎擾
	HWND GetHandle()
	{
		return m_handle;
	}

	// �I���R�[�h�̎擾
	int GetExitValue()
	{
		return m_messageInfo.wParam;
	}



	// ���� ----------------------------------------------------
public:
	// ���b�Z�[�W�̏���
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



	// �������� ------------------------------------------------
private:
	// ������
	HRESULT Initialize(LPCWSTR title)
	{
		LPCWCHAR CLASS_NAME = L"GameWindowClass";
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

		int windowWidth = rect.right - rect.left;
		int windowHeight = rect.bottom - rect.top;


		// �E�B���h�E�̍쐬
		m_handle = CreateWindow(
			CLASS_NAME,
			title,
			windowStyle,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			windowWidth,
			windowHeight,
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



	// �N���X���� ----------------------------------------------
public:
	// �t�@�N�g�����\�b�h
	static Window* Create(LPCWSTR title, int width, int height)
	{
		// �E�C���h�E�I�u�W�F�N�g�̐���
		Window* pWindow = new Window();

		if (!pWindow)
		{
			return nullptr;
		}


		// ������
		if (FAILED(pWindow->Initialize(title, width, height)))
		{
			delete pWindow;
			return nullptr;
		}


		// �E�B���h�E�I�u�W�F�N�g�̐����ɐ���
		return pWindow;
	}

	// �E�B���h�E�E�v���V�[�W��
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




};