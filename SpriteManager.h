////////////////////////////////////////////////////////////////////////////
//! @file   SpriteManager.h
//!
//! @brief  �X�v���C�g�}�l�[�W���[�N���X�̃w�b�_�t�@�C��
//!
//! @date   2016/5/24
//!
//! @author �ߓ��@�D�a
////////////////////////////////////////////////////////////////////////////



// ���d�C���N���[�h�h�~ ---------------------------------------------------
#pragma once

// �w�b�_�̓ǂݍ��� -------------------------------------------------------
#include <SpriteBatch.h>
#include <SpriteFont.h>
#include <SimpleMath.h>
#include <WICTextureLoader.h>
#include <CommonStates.h>
#include <vector>

#include "Sprite.h"
#include "..\System\Window\Window.h"
#include "..\System\Direct3D\Direct3D.h"
#include "..\Utility\CommonStates\CommonStatesHelper.h"




// ------------------------------------------------------------------------
// SpriteManager�N���X
// ------------------------------------------------------------------------
class SpriteManager
{
	// �^ ----------------------------------------------------------------
	using Textue = Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>;
	using Vec2 = DirectX::SimpleMath::Vector2;


	// �ÓI�����o�ϐ� -----------------------------------------------------
private:

	static SpriteManager*					m_pSpriteManager;	// SpriteManager�̃|�C���^


	// �����o�ϐ� ---------------------------------------------------------
private:

	std::unique_ptr<DirectX::SpriteBatch>	m_Sprite;			// �X�v���C�g�o�b�`
	std::unique_ptr<DirectX::SpriteFont>	m_pSpriteFont;		// �X�v���C�g�t�H���g 
	wchar_t*								m_Path;				// �p�X�w��



	// �R���X�g���N�^ ------------------------------------------------------
public:
	SpriteManager() = default;


	// �f�X�g���N�^ --------------------------------------------------------
public:
	~SpriteManager() = default;



	//	�����o�֐� ----------------------------------------------------------
private:

	// --------------------------------------------------------------------
	//! @brief		������
	// --------------------------------------------------------------------
	void Initialize()
	{
		// �X�v���C�g�o�b�`�̐���
		m_Sprite = std::make_unique<DirectX::SpriteBatch>(Direct3D::GetInstance()->GetDeviceContext());

		// �X�v���C�g�t�H���g�̐���
		m_pSpriteFont = std::make_unique<DirectX::SpriteFont>(Direct3D::GetInstance()->GetDevice(),
			L"Resources/Fonts/msgothic.spritefont");

		// �p�X���w�肷��
		m_Path = L"Resources/Images/";
	}



public:

	// --------------------------------------------------------------------
	//! @brief      �`��	
	//!
	//! @param[in]	Sprite		�`��摜
	//! @param[in]	Vector2		�`����W
	// --------------------------------------------------------------------
	void Render(Sprite* pSprite, Vec2 const& position)
	{
		// �R�����X�e�[�g�I�u�W�F�N�g�̃A�h���X��Ⴄ
		auto comaStates = CommonStatesHelper::GetInstance()->GetCommonStates();

		// �`�揈��
		// �摜�̓��ߐF��`�悷��
		m_Sprite->Begin(DirectX::SpriteSortMode::SpriteSortMode_Deferred, comaStates->NonPremultiplied());

		pSprite->Draw(m_Sprite.get(), position);

		m_Sprite->End();
	}


	// --------------------------------------------------------------------
	//! @brief      �X�v���C�g�̐���	
	//!
	//! @param[in]  wstring&		�`�悷��摜�̖��O
	//! @param[in]	RECT			�؂���摜�T�C�Y
	//!
	//! @return     nullptr			�X�v���C�g�̐����Ɏ��s
	//! @return		Sprite			�X�v���C�g�̐����ɐ���
	// --------------------------------------------------------------------
	Sprite* CreateSprite(const std::wstring& filename, const RECT textureRegion)
	{
		// �摜�̓ǂݍ��� 
		std::wstring textueName = m_Path + filename;

		// �e�N�X�`��
		Textue	pTextue;

		// �e�N�X�`���̐���
		HRESULT hr = DirectX::CreateWICTextureFromFile(Direct3D::GetInstance()->GetDevice(),
													   Direct3D::GetInstance()->GetDeviceContext(),
													   textueName.c_str(),
													   nullptr,
													   pTextue.GetAddressOf());

		// �G���[�`�F�b�N
		if (FAILED(hr))
		{
			MessageBox(nullptr, L"�摜�̓ǂݍ��݂Ɏ��s���܂���", L"Error [SpriteManager:CreateSprite]", MB_OK | MB_ICONINFORMATION);
			return nullptr;
		}

		// �X�v���C�g�̐���
		return new Sprite(pTextue, textureRegion);
	}

	// ---------------------------------------------------------------------------
	//! @brief      �X�v���C�g�̐���	
	//!
	//! @param[in]  filename		�`�悷��摜�̖��O
	//!
	//! @return     nullptr			�X�v���C�g�̐����Ɏ��s
	//! @return		Sprite			�X�v���C�g�̐����ɐ���
	// ---------------------------------------------------------------------------
	Sprite* CreateSprite(const std::wstring& filename)
	{
		// �摜�̓ǂݍ��� 
		std::wstring textueName = m_Path + filename;

		// �e�N�X�`��
		Textue	pTextue;

		HRESULT hr = DirectX::CreateWICTextureFromFile(Direct3D::GetInstance()->GetDevice(),
			Direct3D::GetInstance()->GetDeviceContext(),
			textueName.c_str(),
			nullptr,
			pTextue.GetAddressOf());


		// �G���[�`�F�b�N
		if (FAILED(hr))
		{
			MessageBox(nullptr, L"�摜�̓ǂݍ��݂Ɏ��s���܂���", L"Error [SpriteManager:CreateSprite]", MB_OK | MB_ICONINFORMATION);
			return nullptr;
		}


		// �摜�̏c�������߂�
		Microsoft::WRL::ComPtr<ID3D11Resource> pResource = nullptr;
		pTextue->GetResource(&pResource);

		ID3D11Texture2D* pTexture2D = static_cast<ID3D11Texture2D*>(pResource.Get());
		D3D11_TEXTURE2D_DESC textureDesc;
		pTexture2D->GetDesc(&textureDesc);

		// �摜�T�C�Y��ݒ�
		RECT region = { 0, 0, static_cast<LONG>(textureDesc.Width), static_cast<LONG>(textureDesc.Height)};

		// �X�v���C�g�̐���
		return new Sprite(pTextue, region);
	}






	// �ÓI�����o�֐� -----------------------------------------------------------
public:

	// ----------------------------------------------------------------------
	//! @brief		�X�v���C�g�}�l�[�W���ւ̃A�h���X���擾����
	//!
	//! @return     SpriteManager
	// ----------------------------------------------------------------------
	static SpriteManager* GetInstance()
	{
		// �w���p�[����̏ꍇ����
		if (m_pSpriteManager == nullptr)
			SpriteManager::Create();

		return m_pSpriteManager;
	}



private:


	// ---------------------------------------------------------------------------
	//! @brief      �X�v���C�g�}�l�[�W���[�̐���
	// ---------------------------------------------------------------------------
	static void Create()
	{
		// �X�v���C�g�}�l�[�W���̐���
		m_pSpriteManager  = new SpriteManager();

		// �X�v���C�g�}�l�[�W����������
		m_pSpriteManager->Initialize();
	}

};