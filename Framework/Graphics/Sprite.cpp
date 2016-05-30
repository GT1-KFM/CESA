////////////////////////////////////////////////////////////////////////////
//! @file   Sprite.cpp
//!
//! @brief  スプタイトのヘッダファイル
//!
//! @date   2016/5/23
//!
//! @author 近藤　優和
////////////////////////////////////////////////////////////////////////////


// ヘッダファイルの読み込み
#include "Sprite.h"


// 名前空間の使用宣言
using namespace std;
using namespace DirectX;
using namespace SimpleMath;



// ---------------------------------------------------------------------------
//! @brief      コンストラクタ
// ---------------------------------------------------------------------------
Sprite::Sprite(Textue pTextue, RECT textureRegion)
	:m_pTextue(pTextue)
	, m_textureRegion(textureRegion)
{
	// カラーを標準色、ホワイトに設定
	this->SetColor(Colors::White);
	// 原点を(0,0)に設定
	this->SetOrigin(Vector2(0.0f,0.0f));
	// 回転角を(0.0f)に設定
	this->SetRotationAngle(0.0f);
	// 縮尺を(1,1)に設定
	this->SetScale(1);
}






// ---------------------------------------------------------------------------
//! @brief      デストラクタ
// ---------------------------------------------------------------------------
Sprite::~Sprite()
{
}




//------------------------------------------------------------------
//! @brief 回転角の設定
//!
//! @param[in] rotationAngle 回転角[度]
//!
//! @return なし
//------------------------------------------------------------------
void Sprite::SetRotationAngle(float rotationAngle)
{
	m_rotationAngle = XMConvertToRadians(-rotationAngle);
}





//------------------------------------------------------------------
//! @brief 縮尺の設定
//!
//! @param[in] scale 縮尺
//!
//! @return なし
//------------------------------------------------------------------
void Sprite::SetScale(float scale)
{
	m_scale = Vec2(scale,scale);
}





//------------------------------------------------------------------
//! @brief 縮尺の設定
//!
//! @param[in] scaleX X軸方向の縮尺
//! @param[in] scaleY Y軸方向の縮尺
//!
//! @return なし
//------------------------------------------------------------------
void Sprite::SetScale(float scaleX, float scaleY)
{
	m_scale = Vec2(scaleX, scaleY);
}





//------------------------------------------------------------------
//! @brief 原点の設定
//!
//! @param[in] origin 原点
//!
//! @return なし
//------------------------------------------------------------------
void Sprite::SetOrigin(const Vec2& origin)
{
	m_origin.x = static_cast<float>(origin.x);
	m_origin.y = static_cast<float>(origin.y);
}







//------------------------------------------------------------------
//! @brief 描画色の設定
//!
//! @param[in] color 描画色
//!
//! @return なし
//------------------------------------------------------------------
void Sprite::SetColor(const Color& color)
{
	m_color = color;
}






//------------------------------------------------------------------
//! @brief 描画色の設定
//!
//! @param[in] color 描画色(標準色)
//!
//! @return なし
//------------------------------------------------------------------
void Sprite::SetColor(const DirectX::XMVECTOR& color)
{
	SetColor(static_cast<Color>(color));
}





//------------------------------------------------------------------
//! @brief 透明色の設定
//!
//! @param[in] color 描画色(標準色)
//!
//! @return なし
//------------------------------------------------------------------
void Sprite::SetAlpha(float alpha)
{
	m_color.A(alpha);
}




//------------------------------------------------------------------
//! @brief 描画色の設定
//!
//! @param[in] color 描画色(標準色)
//!
//! @return なし
//------------------------------------------------------------------
void Sprite::Draw(DirectX::SpriteBatch* spriteBatch, const Vec2& position)
{
	spriteBatch->Draw(m_pTextue.Get(), position, &m_textureRegion, m_color, m_rotationAngle, m_origin, m_scale);
}