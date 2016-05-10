//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Direct3D.cpp
//!
//! @brief  Direct3D�N���X�̃\�[�X�t�@�C��
//!
//! @date   2014/10/10
//!
//! @author ���� �W
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "Direct3D.h"




// ���C�u�����̒ǉ� ========================================================
#pragma comment(lib, "d3d11.lib")    // Direct3D11�p���C�u����




// �����o�֐��̒�` ========================================================
namespace Framework
{
	/*
	//------------------------------------------------------------------
	//! @brief �f�t�H���g�R���X�g���N�^
	//!
	//! @param �Ȃ�
	//------------------------------------------------------------------
	Direct3D::Direct3D()
		: m_hWindow(nullptr)
		, m_pDevice(nullptr)
		, m_pImmediateContext(nullptr)
		, m_pSwapChain(nullptr)
		, m_pRenderTargetView(nullptr)
		, m_pDepthStencilView(nullptr)
		, m_renderTargetWidth(0)
		, m_renderTargetHeight(0)
	{
	}



	//------------------------------------------------------------------
	//! @brief �f�o�C�X�̎擾
	//!
	//! @param �Ȃ�
	//!
	//! @return �f�o�C�X
	//------------------------------------------------------------------
	ID3D11Device* Direct3D::GetDevice() const
	{
		return m_pDevice.Get();
	}



	//------------------------------------------------------------------
	//! @brief �f�o�C�X�R���e�L�X�g�̎擾
	//!
	//! @param �Ȃ�
	//!
	//! @return �f�o�C�X�R���e�L�X�g(�C�~�f�B�G�C�g�R���e�L�X�g)
	//------------------------------------------------------------------
	ID3D11DeviceContext* Direct3D::GetDeviceContext() const
	{
		return m_pImmediateContext.Get();
	}



	//------------------------------------------------------------------
	//! @brief �X���b�v�`�F�[���̎擾
	//!
	//! @param �Ȃ�
	//!
	//! @return �X���b�v�`�F�[��
	//------------------------------------------------------------------
	IDXGISwapChain* Direct3D::GetSwapChain() const
	{
		return m_pSwapChain.Get();
	}



	//------------------------------------------------------------------
	//! @brief �����_�[�^�[�Q�b�g�r���[�̎擾
	//!
	//! @param �Ȃ�
	//!
	//! @return �����_�[�^�[�Q�b�g�r���[
	//------------------------------------------------------------------
	ID3D11RenderTargetView* Direct3D::GetRenderTargetView() const
	{
		return m_pRenderTargetView.Get();
	}



	//------------------------------------------------------------------
	//! @brief �[�x�X�e���V���r���[�̎擾
	//!
	//! @param �Ȃ�
	//!
	//! @return �[�x�X�e���V���r���[
	//------------------------------------------------------------------
	ID3D11DepthStencilView* Direct3D::GetDepthStencilView() const
	{
		return m_pDepthStencilView.Get();
	}



	//------------------------------------------------------------------
	//! @brief �\�����[�h�̐ݒ�
	//!
	//! @param[in] isFullscreen �t���X�N���[���ɂ��邩�ǂ���
	//!
	//! @return �Ȃ�
	//------------------------------------------------------------------
	HRESULT Direct3D::SetFullscreenState(bool isFullscreen)
	{
		return m_pSwapChain->SetFullscreenState(isFullscreen, nullptr);
	}



	//------------------------------------------------------------------
	//! @brief �f�o�C�X���\�[�X�̍쐬
	//!
	//! @param �Ȃ�
	//!
	//! @return �Ȃ�
	//!
	//! @exception COM���\�b�h�̎��s���ʂ��G���[�̏ꍇ�ACOM��O�I�u�W�F�N�g�𑗏o
	//------------------------------------------------------------------
	void Direct3D::CreateDeviceResources()
	{
		// �f�o�C�X�쐬�t���O�̐ݒ�
		UINT creationFlags = 0;    // �f�o�C�X�쐬�Ŏg�p����p�����[�^�[

		creationFlags |= D3D11_CREATE_DEVICE_BGRA_SUPPORT;    // Direct3D���\�[�X�Ƃ̑��݉^�p����Direct2D�Ŏ������邽�߂ɕK�v
#if defined(_DEBUG)
		creationFlags |= D3D11_CREATE_DEVICE_DEBUG;           // SDK���C���[�ɂ��f�o�b�O��L����(Debug���̂�)
#endif


		// �T�|�[�g�����DirectX�n�[�h�E�F�A�@�\���x���̃Z�b�g�̒�`(���Ԃɒ���)
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
		THROW_IF_FAILED(
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
			)
		);
	}



	//------------------------------------------------------------------
	//! @brief �E�B���h�E�T�C�Y�Ɉˑ����郊�\�[�X�̍쐬
	//!
	//! @param �Ȃ�
	//!
	//! @return �Ȃ�
	//------------------------------------------------------------------
	void Direct3D::CreateWindowSizeDependentResources()
	{
		// �����_�[�^�[�Q�b�g�̃T�C�Y�̎Z�o
		RECT clientArea;
		GetClientRect(m_hWindow, &clientArea);

		m_renderTargetWidth  = clientArea.right  - clientArea.left;
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


	
	//------------------------------------------------------------------
	//! @brief �X���b�v�`�F�[���̍쐬
	//!
	//! @param �Ȃ�
	//!
	//! @return �Ȃ�
	//!
	//! @exception COM���\�b�h�̎��s���ʂ��G���[�̏ꍇ�ACOM��O�I�u�W�F�N�g�𑗏o
	//------------------------------------------------------------------
	void Direct3D::CreateSwapChain()
	{
		// �X���b�v�`�F�C���̐ݒ���w��
		DXGI_SWAP_CHAIN_DESC swapChainDesc;
		ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

		swapChainDesc.BufferDesc.Width   = m_renderTargetWidth;                // �����_�[�^�[�Q�b�g�̃T�C�Y�ƈ�v������
		swapChainDesc.BufferDesc.Height  = m_renderTargetHeight;
		swapChainDesc.BufferDesc.Format  = DXGI_FORMAT_B8G8R8A8_UNORM;         // �ł���ʓI�ȃX���b�v�`�F�[���̃t�H�[�}�b�g���w��
		swapChainDesc.SampleDesc.Count   = 1;                                  // �}���`�T���v�����O�s�g�p
		swapChainDesc.SampleDesc.Quality = 0;
		swapChainDesc.BufferUsage        = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferCount        = 2;                                  // �x�����ŏ����ɗ}���邽�߂Ƀ_�u���o�b�t�@���g�p
		swapChainDesc.OutputWindow       = m_hWindow;
		swapChainDesc.Windowed           = TRUE;
		swapChainDesc.SwapEffect         = DXGI_SWAP_EFFECT_DISCARD;
		swapChainDesc.Flags              = 0;


		// Direct3D�f�o�C�X���쐬����ۂɎg�p���ꂽDXGI�t�@�N�g�����擾���ăX���b�v�`�F�[�����쐬
		ComPtr<IDXGIDevice> dxgiDevice;
		THROW_IF_FAILED(
			m_pDevice.As(&dxgiDevice)
		);

		ComPtr<IDXGIAdapter> dxgiAdapter;
		THROW_IF_FAILED(
			dxgiDevice->GetAdapter(&dxgiAdapter)
		);

		ComPtr<IDXGIFactory> dxgiFactory;
		THROW_IF_FAILED(
			dxgiAdapter->GetParent(IID_PPV_ARGS(&dxgiFactory))
		);

		THROW_IF_FAILED(
			dxgiFactory->CreateSwapChain(m_pDevice.Get(), &swapChainDesc, &m_pSwapChain)
		);


		// �t���X�N���[���̕s��𒼂����߂Ƀo�b�t�@�����T�C�Y
		m_pSwapChain->ResizeBuffers(swapChainDesc.BufferCount, 0, 0, DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH);
	}



	//------------------------------------------------------------------
	//! @brief �����_�[�^�[�Q�b�g�r���[�̍쐬
	//!
	//! @param �Ȃ�
	//!
	//! @return �Ȃ�
	//!
	//! @exception COM���\�b�h�̎��s���ʂ��G���[�̏ꍇ�ACOM��O�I�u�W�F�N�g�𑗏o
	//------------------------------------------------------------------
	void Direct3D::CreateRenderTargetView()
	{
		ComPtr<ID3D11Texture2D> pBackBuffer;
		THROW_IF_FAILED(
			m_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer))
		);

		THROW_IF_FAILED(
			m_pDevice->CreateRenderTargetView(pBackBuffer.Get(), nullptr, &m_pRenderTargetView)
		);
	}



	//------------------------------------------------------------------
	//! @brief �[�x�X�e���V���r���[�̍쐬
	//!
	//! @param �Ȃ�
	//!
	//! @return �Ȃ�
	//!
	//! @exception COM���\�b�h�̎��s���ʂ��G���[�̏ꍇ�ACOM��O�I�u�W�F�N�g�𑗏o
	//------------------------------------------------------------------
	void Direct3D::CreateDepthStencilView()
	{
		// �X���b�v�`�F�[���̐ݒ���擾
		DXGI_SWAP_CHAIN_DESC swapChainDesc;
		m_pSwapChain->GetDesc(&swapChainDesc);


		// �[�x�X�e���V���̐ݒ�̎w��
		D3D11_TEXTURE2D_DESC depthStencilDesc;
		ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));

		depthStencilDesc.Width          = m_renderTargetWidth;              // �����_�[�^�[�Q�b�g�̃T�C�Y�ƈ�v������
		depthStencilDesc.Height         = m_renderTargetHeight; 
		depthStencilDesc.MipLevels      = 1;                                // �~�b�v�}�b�v���쐬���Ȃ�
		depthStencilDesc.ArraySize      = 1;                                // �e�N�X�`���[�̖�����1��
		depthStencilDesc.Format         = DXGI_FORMAT_D24_UNORM_S8_UINT;    // �t�H�[�}�b�g
		depthStencilDesc.SampleDesc     = swapChainDesc.SampleDesc;         // �X���b�v�`�F�[���Ɉ�v������
		depthStencilDesc.Usage          = D3D11_USAGE_DEFAULT;              // GPU�ɂ��ǂݏ����A�N�Z�X��K�v�Ƃ��郊�\�[�X
		depthStencilDesc.BindFlags      = D3D11_BIND_DEPTH_STENCIL;         // �e�N�X�`���[��[�x�X�e���V���^�[�Q�b�g�Ƃ��ăo�C���h
		depthStencilDesc.CPUAccessFlags = 0;                                // CPU�A�N�Z�X���s�v�B
		depthStencilDesc.MiscFlags      = 0;                                // ���̑��̃t���O���ݒ肵�Ȃ�		


		// �[�x�X�e���V���̍쐬
		ComPtr<ID3D11Texture2D> depthStencil;
		THROW_IF_FAILED(
			m_pDevice->CreateTexture2D(&depthStencilDesc, nullptr, &depthStencil)
		);


		// �[�x�X�e���V���r���[�̐ݒ�̎w��
		D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
		ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));

		depthStencilViewDesc.Format        = depthStencilDesc.Format;          // �[�x�X�e���V���Ɉ�v������
		depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;    // �}���`�T���v�����O�s�g�p


		// �[�x�X�e���V���r���[�̍쐬
		THROW_IF_FAILED(
			m_pDevice->CreateDepthStencilView(depthStencil.Get(), &depthStencilViewDesc, &m_pDepthStencilView)
		);
	}



	//------------------------------------------------------------------
	//! @brief �f�o�C�X�Ƀ����_�[�^�[�Q�b�g����ѐ[�x�X�e���V���r���[���o�C���h
	//!
	//! @param �Ȃ�
	//!
	//! @return �Ȃ�
	//------------------------------------------------------------------
	void Direct3D::BindRenderTarget()
	{
		ID3D11RenderTargetView* targets[] = { m_pRenderTargetView.Get() };
		m_pImmediateContext->OMSetRenderTargets(1, targets, m_pDepthStencilView.Get());
	}



	//------------------------------------------------------------------
	//! @brief �r���[�|�[�g�̐ݒ�
	//!
	//! @param �Ȃ�
	//!
	//! @return �Ȃ�
	//------------------------------------------------------------------
	void Direct3D::SetViewPort()
	{
		// �����_�����O�r���[�|�[�g���E�B���h�E�S�̂��^�[�Q�b�g�ɂ���悤�ɐݒ�
		D3D11_VIEWPORT viewport;

		viewport.TopLeftX = 0.0f;
		viewport.TopLeftY = 0.0f;
		viewport.Width    = static_cast<FLOAT>(m_renderTargetWidth);
		viewport.Height   = static_cast<FLOAT>(m_renderTargetHeight);
		viewport.MinDepth = D3D11_MIN_DEPTH;
		viewport.MaxDepth = D3D11_MAX_DEPTH;

		m_pImmediateContext->RSSetViewports(1, &viewport);
	}



	//------------------------------------------------------------------
	//! @brief ������
	//!
	//! @param[in] hWindow �E�B���h�E�n���h��
	//!
	//! @retval S_OK         �������ɐ���
	//! @retval �G���[�R�[�h �������Ɏ��s
	//------------------------------------------------------------------
	HRESULT Direct3D::Initialize(HWND hWindow)
	{
		m_hWindow = hWindow;


		// ���\�[�X�̍쐬
		try {
			CreateDeviceResources();
			CreateWindowSizeDependentResources();
		}
		catch (ComException& exception)
		{
			exception.PopUpMessageBox();
			return exception.GetErrorCode();
		}


		// �������ɐ���
		return S_OK;
	}
}




// �ÓI�����o�֐��̒�` ======================================================
namespace Framework
{
	//------------------------------------------------------------------
	//! @brief Direct3D�I�u�W�F�N�g�̐���
	//!
	//! @param[in] hWindow �E�B���h�E�n���h��
	//!
	//! @retval Direct3D�I�u�W�F�N�g ����
	//! @retval nullptr              ���s
	//------------------------------------------------------------------
	Direct3D* Direct3D::Create(HWND hWindow)
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
	*/
}