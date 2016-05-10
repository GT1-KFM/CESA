//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Direct3D.h
//!
//! @brief  Direct3D�N���X�̃w�b�_�t�@�C��
//!
//! @date   2014/11/10
//!
//! @author ���� �W
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// ���d�C���N���[�h�h�~ ====================================================
#pragma once




// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include <Windows.h>

#include <d3d11.h>

#include "Framework\Utility\ComHelper.h"




// �N���X��` ==============================================================
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//! @brief Direct3D�N���X
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
class Direct3D final
{
	// �����o�ϐ� ----------------------------------------------
private:
	//HWND m_hWindow;   //!< �E�B���h�E�n���h��

	// Direct3D�I�u�W�F�N�g
	ComPtr<ID3D11Device>           m_pDevice = nullptr;   //!< �f�o�C�X
	ComPtr<ID3D11DeviceContext>	   m_pImmediateContext = nullptr;   //!< �C�~�f�B�G�C�g�R���e�L�X�g
	ComPtr<IDXGISwapChain>		   m_pSwapChain = nullptr;   //!< �X���b�v�`�F�[��

	// Direct3D�����_�����O�I�u�W�F�N�g
	ComPtr<ID3D11RenderTargetView> m_pRenderTargetView = nullptr;   //!< �����_�[�^�[�Q�b�g�r���[
	ComPtr<ID3D11DepthStencilView> m_pDepthStencilView = nullptr;   //!< �[�x�X�e���V���r���[

	// �f�o�C�X�v���p�e�B
	UINT						   m_renderTargetWidth = 0;			//!< �����_�[�^�[�Q�b�g�̕�
	UINT						   m_renderTargetHeight = 0;		//!< �����_�[�^�[�Q�b�g�̍���

	static Direct3D*			   m_pDirect3D;

	// �R���X�g���N�^ ------------------------------------------
private:
	Direct3D()
	{
	}



	// �f�X�g���N�^ --------------------------------------------
public:
	// = default ��ɂȂ�
	~Direct3D() = default;



	// ���� ----------------------------------------------------
public:

	// DrirectX3D�I�u�W�F�N�g�ւ̃A�h���X���擾����
	static Direct3D* GetInstance()
	{
		if (m_pDirect3D == nullptr)
		{
			m_pDirect3D = new Direct3D();
		}

		return m_pDirect3D;
	}


	// �f�o�C�X�̎擾
	ID3D11Device* GetDevice()
	{
		return m_pDevice.Get();
	}

	// �f�o�C�X�R���e�L�X�g�̎擾
	ID3D11DeviceContext* GetDeviceContext()
	{
		return m_pImmediateContext.Get();
	}

	// �X���b�v�`�F�[���̎擾
	IDXGISwapChain* GetSwapChain()
	{
		return m_pSwapChain.Get();
	}

	// �����_�[�^�[�Q�b�g�r���[�̎擾
	ID3D11RenderTargetView* GetRenderTargetView()
	{
		return m_pRenderTargetView.Get();
	}

	// �[�x�X�e���V���r���[�̎擾
	ID3D11DepthStencilView* GetDepthStencilView()
	{
		return m_pDepthStencilView.Get();
	}



	// ���� ----------------------------------------------------
public:
	// �\�����[�h�̐ݒ�
	HRESULT SetFullscreenState(bool isFullscreen)
	{
		return m_pSwapChain->SetFullscreenState(isFullscreen, NULL);
	}



	// �������� ------------------------------------------------
private:
	// �f�o�C�X���\�[�X�̍쐬
	void CreateDeviceResources()
	{

		// �f�o�C�X�쐬�t���O�̐ݒ�
		UINT creationFlags = 0;    // �f�o�C�X�쐬�Ŏg�p����p�����[�^�[

		creationFlags |= D3D11_CREATE_DEVICE_BGRA_SUPPORT;    // Direct3D���\�[�X�Ƃ̑��݉^�p����Direct2D�Ŏ������邽�߂ɕK�v
#if defined(_DEBUG)
		creationFlags |= D3D11_CREATE_DEVICE_DEBUG;           // SDK���C���[�ɂ��f�o�b�O��L����(Debug���̂�)
#endif


															  // �T�|�[�g�����DirectX�n�[�h�E�F�A�@�\���x���̃Z�b�g�̒�`(���Ԃɒ���)											  // �T�|�[�g�����DirectX�n�[�h�E�F�A�@�\���x���̃Z�b�g�̒�`(���Ԃɒ���)
		D3D_FEATURE_LEVEL featureLevels[] =
		{
			D3D_FEATURE_LEVEL_11_1,
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_10_0,
			D3D_FEATURE_LEVEL_9_3,
			D3D_FEATURE_LEVEL_9_2,
			D3D_FEATURE_LEVEL_9_1
		};

		D3D_FEATURE_LEVEL featureLevel;    //!< �f�o�C�X�̋@�\���x��


										   // Direct3D11�f�o�C�X�I�u�W�F�N�g����ёΉ�����f�o�C�X�R���e�L�X�g�̍쐬
		D3D11CreateDevice(
			nullptr,                     // [in]  ����̃A�_�v�^�[���g�p���邽��nullptr���w��
			D3D_DRIVER_TYPE_HARDWARE,    // [in]  �n�[�h�E�F�A�O���t�B�b�N�X�h���C�o�[���g�p
			nullptr,                     // [in]  D3D_DRIVER_TYPE_SOFTWARE�łȂ�����nullptr���w��
			creationFlags,               // [in]  �L���ɂ��郉���^�C�����C���[�̎w��
			featureLevels,               // [in]  ���̃A�v�����T�|�[�g�ł���@�\���x���̈ꗗ
			ARRAYSIZE(featureLevels),    // [in]  ��L���X�g�̗v�f��
			D3D11_SDK_VERSION,           // [in]  SDK�̃o�[�W����(���D3D11_SDK_VERSION)���w��
			&m_pDevice,                  // [out] �쐬���ꂽ�f�o�C�X
			&featureLevel,               // [out] �쐬���ꂽ�f�o�C�X�̋@�\���x��(���s�����ꍇ��0)
			&m_pImmediateContext         // [out] �f�o�C�X�̃C�~�f�B�G�C�g�R���e�L�X�g
			);
	}
	

	// �E�B���h�E�T�C�Y�Ɉˑ����郊�\�[�X�̍쐬
	void CreateWindowSizeDependentResources()
	{
		// �����_�[�^�[�Q�b�g�̃T�C�Y�̎Z�o
		RECT clientArea;
		GetClientRect(Window::, &clientArea);

		m_renderTargetWidth = clientArea.right - clientArea.left;
		m_renderTargetHeight = clientArea.bottom - clientArea.top;


		// �X���b�v�`�F�[���̍쐬
		CreateSwapChain();

		// �����_�[�^�[�Q�b�g�r���[�̍쐬
		CreateRenderTargetView();

		// �[�x�X�e���V���r���[�̍쐬
		CreateDepthStencilView();


		// �f�o�C�X�Ƀ����_�[�^�[�Q�b�g����ѐ[�x�X�e���V���r���[���o�C���h
		BindRenderTarget();


		// �r���[�|�[�g�̐ݒ�
		SetViewPort();
	}

	// �X���b�v�`�F�[���̍쐬
	void CreateSwapChain()
	{
		// �X���b�v�`�F�C���̐ݒ���w��
		DXGI_SWAP_CHAIN_DESC swapChainDesc;
		ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

		swapChainDesc.BufferDesc.Width = m_renderTargetWidth;                // �����_�[�^�[�Q�b�g�̃T�C�Y�ƈ�v������
		swapChainDesc.BufferDesc.Height = m_renderTargetHeight;
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;         // �ł���ʓI�ȃX���b�v�`�F�[���̃t�H�[�}�b�g���w��
		swapChainDesc.SampleDesc.Count = 1;                                  // �}���`�T���v�����O�s�g�p
		swapChainDesc.SampleDesc.Quality = 0;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferCount = 2;                                  // �x�����ŏ����ɗ}���邽�߂Ƀ_�u���o�b�t�@���g�p
		swapChainDesc.OutputWindow = m_hWindow;
		swapChainDesc.Windowed = TRUE;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		swapChainDesc.Flags = 0;


		// Direct3D�f�o�C�X���쐬����ۂɎg�p���ꂽDXGI�t�@�N�g�����擾���ăX���b�v�`�F�[�����쐬
		ComPtr<IDXGIDevice> dxgiDevice;
		m_pDevice.As(&dxgiDevice);

		ComPtr<IDXGIAdapter> dxgiAdapter;
		dxgiDevice->GetAdapter(&dxgiAdapter);

		ComPtr<IDXGIFactory> dxgiFactory;
		dxgiAdapter->GetParent(IID_PPV_ARGS(&dxgiFactory));

		dxgiFactory->CreateSwapChain(m_pDevice.Get(), &swapChainDesc, &m_pSwapChain);


		// �t���X�N���[���̕s��𒼂����߂Ƀo�b�t�@�����T�C�Y
		m_pSwapChain->ResizeBuffers(swapChainDesc.BufferCount, 0, 0, DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH);

	}

	// �����_�[�^�[�Q�b�g�r���[�̍쐬
	void CreateRenderTargetView()
	{
		ComPtr<ID3D11Texture2D> pBackBuffer;
		m_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));

		m_pDevice->CreateRenderTargetView(pBackBuffer.Get(), nullptr, &m_pRenderTargetView);
	}

	// �[�x�X�e���V���r���[�̍쐬
	void CreateDepthStencilView()
	{
		// �X���b�v�`�F�[���̐ݒ���擾
		DXGI_SWAP_CHAIN_DESC swapChainDesc;
		m_pSwapChain->GetDesc(&swapChainDesc);


		// �[�x�X�e���V���̐ݒ�̎w��
		D3D11_TEXTURE2D_DESC depthStencilDesc;
		ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));

		depthStencilDesc.Width = m_renderTargetWidth;              // �����_�[�^�[�Q�b�g�̃T�C�Y�ƈ�v������
		depthStencilDesc.Height = m_renderTargetHeight;
		depthStencilDesc.MipLevels = 1;                                // �~�b�v�}�b�v���쐬���Ȃ�
		depthStencilDesc.ArraySize = 1;                                // �e�N�X�`���[�̖�����1��
		depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;    // �t�H�[�}�b�g
		depthStencilDesc.SampleDesc = swapChainDesc.SampleDesc;         // �X���b�v�`�F�[���Ɉ�v������
		depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;              // GPU�ɂ��ǂݏ����A�N�Z�X��K�v�Ƃ��郊�\�[�X
		depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;         // �e�N�X�`���[��[�x�X�e���V���^�[�Q�b�g�Ƃ��ăo�C���h
		depthStencilDesc.CPUAccessFlags = 0;                                // CPU�A�N�Z�X���s�v�B
		depthStencilDesc.MiscFlags = 0;                                // ���̑��̃t���O���ݒ肵�Ȃ�		


																	   // �[�x�X�e���V���̍쐬
		ComPtr<ID3D11Texture2D> depthStencil;
		m_pDevice->CreateTexture2D(&depthStencilDesc, nullptr, &depthStencil);


		// �[�x�X�e���V���r���[�̐ݒ�̎w��
		D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
		ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));

		depthStencilViewDesc.Format = depthStencilDesc.Format;          // �[�x�X�e���V���Ɉ�v������
		depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;    // �}���`�T���v�����O�s�g�p


		// �[�x�X�e���V���r���[�̍쐬
		m_pDevice->CreateDepthStencilView(depthStencil.Get(), &depthStencilViewDesc, &m_pDepthStencilView);
	}

	// �f�o�C�X�Ƀ����_�[�^�[�Q�b�g����ѐ[�x�X�e���V���r���[���o�C���h
	void BindRenderTarget()
	{
		ID3D11RenderTargetView* targets[] = { m_pRenderTargetView.Get() };
		m_pImmediateContext->OMSetRenderTargets(1, targets, m_pDepthStencilView.Get());

	}

	// �r���[�|�[�g�̐ݒ�
	void SetViewPort()
	{
		// �����_�����O�r���[�|�[�g���E�B���h�E�S�̂��^�[�Q�b�g�ɂ���悤�ɐݒ�
		D3D11_VIEWPORT viewport;

		viewport.TopLeftX = 0.0f;
		viewport.TopLeftY = 0.0f;
		viewport.Width = static_cast<FLOAT>(m_renderTargetWidth);
		viewport.Height = static_cast<FLOAT>(m_renderTargetHeight);
		viewport.MinDepth = D3D11_MIN_DEPTH;
		viewport.MaxDepth = D3D11_MAX_DEPTH;

		m_pImmediateContext->RSSetViewports(1, &viewport);
	}

	// ������
	void Initialize(HWND hWindow)
	{
		m_hWindow = Window::GetInstance()->GetHandle();


		// ���\�[�X�̍쐬
		CreateDeviceResources();
		CreateWindowSizeDependentResources();


		
	}



	// �N���X���� ----------------------------------------------
public:
	// �t�@�N�g�����\�b�h
	static Direct3D* Create(HWND hWindow)
	{
		// Direct3D�I�u�W�F�N�g�̐���
		Direct3D* pDirect3D = new Direct3D();

		if (!pDirect3D)
		{
			return nullptr;
		}


		// ������
		if (FAILED(pDirect3D->Initialize(hWindow)))
		{
			delete pDirect3D;
			return nullptr;
		}


		// Direct3D�I�u�W�F�N�g�̐����ɐ���
		return pDirect3D;
	}

};