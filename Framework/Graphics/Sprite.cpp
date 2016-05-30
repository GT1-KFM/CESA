////////////////////////////////////////////////////////////////////////////
//! @file   Sprite.cpp
//!
//! @brief  �X�v�^�C�g�̃w�b�_�t�@�C��
//!
//! @date   2016/5/23
//!
//! @author �ߓ��@�D�a
////////////////////////////////////////////////////////////////////////////


// �w�b�_�t�@�C���̓ǂݍ���
#include "Sprite.h"


// ���O��Ԃ̎g�p�錾
using namespace std;
using namespace DirectX;
using namespace SimpleMath;



// ---------------------------------------------------------------------------
//! @brief      �R���X�g���N�^
// ---------------------------------------------------------------------------
Sprite::Sprite(Textue pTextue, RECT textureRegion)
	:m_pTextue(pTextue)
	, m_textureRegion(textureRegion)
{
	// �J���[��W���F�A�z���C�g�ɐݒ�
	this->SetColor(Colors::White);
	// ���_��(0,0)�ɐݒ�
	this->SetOrigin(Vector2(0.0f,0.0f));
	// ��]�p��(0.0f)�ɐݒ�
	this->SetRotationAngle(0.0f);
	// �k�ڂ�(1,1)�ɐݒ�
	this->SetScale(1);
}






// ---------------------------------------------------------------------------
//! @brief      �f�X�g���N�^
// ---------------------------------------------------------------------------
Sprite::~Sprite()
{
}




//------------------------------------------------------------------
//! @brief ��]�p�̐ݒ�
//!
//! @param[in] rotationAngle ��]�p[�x]
//!
//! @return �Ȃ�
//------------------------------------------------------------------
void Sprite::SetRotationAngle(float rotationAngle)
{
	m_rotationAngle = XMConvertToRadians(-rotationAngle);
}





//------------------------------------------------------------------
//! @brief �k�ڂ̐ݒ�
//!
//! @param[in] scale �k��
//!
//! @return �Ȃ�
//------------------------------------------------------------------
void Sprite::SetScale(float scale)
{
	m_scale = Vec2(scale,scale);
}





//------------------------------------------------------------------
//! @brief �k�ڂ̐ݒ�
//!
//! @param[in] scaleX X�������̏k��
//! @param[in] scaleY Y�������̏k��
//!
//! @return �Ȃ�
//------------------------------------------------------------------
void Sprite::SetScale(float scaleX, float scaleY)
{
	m_scale = Vec2(scaleX, scaleY);
}





//------------------------------------------------------------------
//! @brief ���_�̐ݒ�
//!
//! @param[in] origin ���_
//!
//! @return �Ȃ�
//------------------------------------------------------------------
void Sprite::SetOrigin(const Vec2& origin)
{
	m_origin.x = static_cast<float>(origin.x);
	m_origin.y = static_cast<float>(origin.y);
}







//------------------------------------------------------------------
//! @brief �`��F�̐ݒ�
//!
//! @param[in] color �`��F
//!
//! @return �Ȃ�
//------------------------------------------------------------------
void Sprite::SetColor(const Color& color)
{
	m_color = color;
}






//------------------------------------------------------------------
//! @brief �`��F�̐ݒ�
//!
//! @param[in] color �`��F(�W���F)
//!
//! @return �Ȃ�
//------------------------------------------------------------------
void Sprite::SetColor(const DirectX::XMVECTOR& color)
{
	SetColor(static_cast<Color>(color));
}





//------------------------------------------------------------------
//! @brief �����F�̐ݒ�
//!
//! @param[in] color �`��F(�W���F)
//!
//! @return �Ȃ�
//------------------------------------------------------------------
void Sprite::SetAlpha(float alpha)
{
	m_color.A(alpha);
}




//------------------------------------------------------------------
//! @brief �`��F�̐ݒ�
//!
//! @param[in] color �`��F(�W���F)
//!
//! @return �Ȃ�
//------------------------------------------------------------------
void Sprite::Draw(DirectX::SpriteBatch* spriteBatch, const Vec2& position)
{
	spriteBatch->Draw(m_pTextue.Get(), position, &m_textureRegion, m_color, m_rotationAngle, m_origin, m_scale);
}