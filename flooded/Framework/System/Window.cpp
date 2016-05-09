// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "Window.h"

// ���O��Ԃ̎g�p�錾 ======================================================
using namespace std;

	// @brief �f�t�H���g�R���X�g���N�^
	// @param �Ȃ�
	Window::Window()
		: m_handle(nullptr)
		, m_messageInfo()
	{
		ZeroMemory(&m_messageInfo, sizeof(m_messageInfo));
	}

	// @brief �E�B���h�E�n���h���̎擾
	// @param �Ȃ�
	// @return �E�B���h�E�n���h��
	HWND Window::GetHandle() const
	{
		return m_handle;
	}

	// @brief �I���R�[�h�̎擾
	// @param �Ȃ�
	// @return �I���R�[�h
	int Window::GetExitValue() const
	{
		return m_messageInfo.wParam;
	}

	// @brief ���b�Z�[�W�̏���
	// @param �Ȃ�
	// @retval true  ���b�Z�[�W������ or WM_QUIT�ȊO�̃��b�Z�[�W�����������ꍇ
	// @retval false WM_QUIT���b�Z�[�W����M�����ꍇ
	bool Window::HandleMessage()
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

	// @brief ������
	// @param[in] title  �E�B���h�E�̃^�C�g��
	// @param[in] width  �N���C�A���g�̈�̕�
	// @param[in] height �N���C�A���g�̈�̍���
	// @retval S_OK   �������ɐ���
	// @retval E_FAIL �������Ɏ��s
	HRESULT Window::Initialize(LPCWSTR title, int width, int height)
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
		RECT rect = { 0, 0, width, height };
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


	// @brief�E�B���h�E�I�u�W�F�N�g�̐���
	// @param[in] title  �E�B���h�E�̃^�C�g��
	// @param[in] width  �N���C�A���g�̈�̕�
	// @param[in] height �N���C�A���g�̈�̍���
	// @retval �E�B���h�E�I�u�W�F�N�g ����
	// @retval nullptr                ���s
	Window* Window::Create(LPCWSTR title, int width, int height)
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

	// @brief �E�B���h�E�E�v���V�[�W��
	// @param[in] hWindow  �E�B���h�E�n���h��
	// @param[in] uMessage ���b�Z�[�W�̎��ʎq
	// @param[in] wParam   ���b�Z�[�W��1�Ԗڂ̃p�����[�^
	// @param[in] lParam   ���b�Z�[�W��2�Ԗڂ̃p�����[�^
	// @return ���b�Z�[�W�����̌���(���M���ꂽ���b�Z�[�W�ɂ���ĈقȂ�)
	LRESULT CALLBACK Window::Procedure(HWND hWindow, UINT uMessage, WPARAM wParam, LPARAM lParam)
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