////////////////////////////////////////////////////////////////////////////
//! @file   SpriteManager.h
//!
//! @brief  スプライトマネージャークラスのヘッダファイル
//!
//! @date   2016/5/24
//!
//! @author 近藤　優和
////////////////////////////////////////////////////////////////////////////



// 多重インクルード防止 ---------------------------------------------------
#pragma once

// ヘッダの読み込み -------------------------------------------------------
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
// SpriteManagerクラス
// ------------------------------------------------------------------------
class SpriteManager
{
	// 型 ----------------------------------------------------------------
	using Textue = Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>;
	using Vec2 = DirectX::SimpleMath::Vector2;


	// 静的メンバ変数 -----------------------------------------------------
private:

	static SpriteManager*					m_pSpriteManager;	// SpriteManagerのポインタ


	// メンバ変数 ---------------------------------------------------------
private:

	std::unique_ptr<DirectX::SpriteBatch>	m_Sprite;			// スプライトバッチ
	std::unique_ptr<DirectX::SpriteFont>	m_pSpriteFont;		// スプライトフォント 
	wchar_t*								m_Path;				// パス指定



	// コンストラクタ ------------------------------------------------------
public:
	SpriteManager() = default;


	// デストラクタ --------------------------------------------------------
public:
	~SpriteManager() = default;



	//	メンバ関数 ----------------------------------------------------------
private:

	// --------------------------------------------------------------------
	//! @brief		初期化
	// --------------------------------------------------------------------
	void Initialize()
	{
		// スプライトバッチの生成
		m_Sprite = std::make_unique<DirectX::SpriteBatch>(Direct3D::GetInstance()->GetDeviceContext());

		// スプライトフォントの生成
		m_pSpriteFont = std::make_unique<DirectX::SpriteFont>(Direct3D::GetInstance()->GetDevice(),
			L"Resources/Fonts/msgothic.spritefont");

		// パスを指定する
		m_Path = L"Resources/Images/";
	}



public:

	// --------------------------------------------------------------------
	//! @brief      描画	
	//!
	//! @param[in]	Sprite		描画画像
	//! @param[in]	Vector2		描画座標
	// --------------------------------------------------------------------
	void Render(Sprite* pSprite, Vec2 const& position)
	{
		// コモンステートオブジェクトのアドレスを貰う
		auto comaStates = CommonStatesHelper::GetInstance()->GetCommonStates();

		// 描画処理
		// 画像の透過色を描画する
		m_Sprite->Begin(DirectX::SpriteSortMode::SpriteSortMode_Deferred, comaStates->NonPremultiplied());

		pSprite->Draw(m_Sprite.get(), position);

		m_Sprite->End();
	}


	// --------------------------------------------------------------------
	//! @brief      スプライトの生成	
	//!
	//! @param[in]  wstring&		描画する画像の名前
	//! @param[in]	RECT			切り取る画像サイズ
	//!
	//! @return     nullptr			スプライトの生成に失敗
	//! @return		Sprite			スプライトの生成に成功
	// --------------------------------------------------------------------
	Sprite* CreateSprite(const std::wstring& filename, const RECT textureRegion)
	{
		// 画像の読み込み 
		std::wstring textueName = m_Path + filename;

		// テクスチャ
		Textue	pTextue;

		// テクスチャの生成
		HRESULT hr = DirectX::CreateWICTextureFromFile(Direct3D::GetInstance()->GetDevice(),
													   Direct3D::GetInstance()->GetDeviceContext(),
													   textueName.c_str(),
													   nullptr,
													   pTextue.GetAddressOf());

		// エラーチェック
		if (FAILED(hr))
		{
			MessageBox(nullptr, L"画像の読み込みに失敗しました", L"Error [SpriteManager:CreateSprite]", MB_OK | MB_ICONINFORMATION);
			return nullptr;
		}

		// スプライトの生成
		return new Sprite(pTextue, textureRegion);
	}

	// ---------------------------------------------------------------------------
	//! @brief      スプライトの生成	
	//!
	//! @param[in]  filename		描画する画像の名前
	//!
	//! @return     nullptr			スプライトの生成に失敗
	//! @return		Sprite			スプライトの生成に成功
	// ---------------------------------------------------------------------------
	Sprite* CreateSprite(const std::wstring& filename)
	{
		// 画像の読み込み 
		std::wstring textueName = m_Path + filename;

		// テクスチャ
		Textue	pTextue;

		HRESULT hr = DirectX::CreateWICTextureFromFile(Direct3D::GetInstance()->GetDevice(),
			Direct3D::GetInstance()->GetDeviceContext(),
			textueName.c_str(),
			nullptr,
			pTextue.GetAddressOf());


		// エラーチェック
		if (FAILED(hr))
		{
			MessageBox(nullptr, L"画像の読み込みに失敗しました", L"Error [SpriteManager:CreateSprite]", MB_OK | MB_ICONINFORMATION);
			return nullptr;
		}


		// 画像の縦横を求める
		Microsoft::WRL::ComPtr<ID3D11Resource> pResource = nullptr;
		pTextue->GetResource(&pResource);

		ID3D11Texture2D* pTexture2D = static_cast<ID3D11Texture2D*>(pResource.Get());
		D3D11_TEXTURE2D_DESC textureDesc;
		pTexture2D->GetDesc(&textureDesc);

		// 画像サイズを設定
		RECT region = { 0, 0, static_cast<LONG>(textureDesc.Width), static_cast<LONG>(textureDesc.Height)};

		// スプライトの生成
		return new Sprite(pTextue, region);
	}






	// 静的メンバ関数 -----------------------------------------------------------
public:

	// ----------------------------------------------------------------------
	//! @brief		スプライトマネージャへのアドレスを取得する
	//!
	//! @return     SpriteManager
	// ----------------------------------------------------------------------
	static SpriteManager* GetInstance()
	{
		// ヘルパーが空の場合生成
		if (m_pSpriteManager == nullptr)
			SpriteManager::Create();

		return m_pSpriteManager;
	}



private:


	// ---------------------------------------------------------------------------
	//! @brief      スプライトマネージャーの生成
	// ---------------------------------------------------------------------------
	static void Create()
	{
		// スプライトマネージャの生成
		m_pSpriteManager  = new SpriteManager();

		// スプライトマネージャを初期化
		m_pSpriteManager->Initialize();
	}

};