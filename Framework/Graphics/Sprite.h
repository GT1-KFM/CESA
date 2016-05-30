////////////////////////////////////////////////////////////////////////////
//! @file   CommonStatesHelper.h
//!
//! @brief  CommonStatesのヘルパークラスのヘッダ
//!
//! @date   
//!
//! @author 近藤　優和
////////////////////////////////////////////////////////////////////////////



// 多重インクルード防止 -----------------------------------------------------
#pragma once



// ヘッダの読み込み ---------------------------------------------------------
#include <SpriteBatch.h>
#include "..\Utility\ComHelper.h"



// --------------------------------------------------------------------------
// Spriteクラス
// --------------------------------------------------------------------------
class Sprite
{
	//friend SpriteManager;
private:
	// 型 ------------------------------------------------------------------
	using Textue = Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>;
	using Color = DirectX::SimpleMath::Color;   
	using Vec2 = DirectX::SimpleMath::Vector2;

	// メンバ変数 ----------------------------------------------------------
private:
	std::unique_ptr < DirectX::SpriteBatch >	m_sprite;				// スプライトバッチ
	Textue										m_pTextue;				// テクスチャ
	RECT										m_textureRegion;		// テクスチャの描画範囲
	Color										m_color;				// 描画色
	Vec2										m_origin;				// 原点
	Vec2                                        m_scale;				// 縮尺
	float										m_rotationAngle;		// 回転角



	// コンストラクタ ------------------------------------------------------
public:
	Sprite(Textue pTextue, RECT textureRegion);

	// デストラクタ
	~Sprite();


	//	メンバ関数 ---------------------------------------------------------
public:

	// テクスチャを得る
	Textue GetTextue() { return m_pTextue.Get(); };

	// テクスチャ範囲を得る
	RECT   GetTextueRegion() { return m_textureRegion; };

	// テクスチャ範囲を設定
	void SetTextueRegion(RECT region) { m_textureRegion = region; };

	// 回転角の設定
	void SetRotationAngle(float rotationAngle);

	// 縮尺の設定
	void SetScale(float scale);

	// 縮尺の設定　XY指定可能
	void SetScale(float scaleX, float scaleY);

	// 原点の設定
	void SetOrigin(const Vec2& origin);

	// 描画色の設定
	void SetColor(const Color& color);

	// 描画色の標準設定
	void Sprite::SetColor(const DirectX::XMVECTOR& color);

	// 透過色の設定
	void SetAlpha(float alpha);

	// 描画
	void Draw(DirectX::SpriteBatch* spriteBatch, const Vec2& position);

};