////////////////////////////////////////////////////////////////////////////
//! @file   CommonStatesHelper.h
//!
//! @brief  CommonStates�̃w���p�[�N���X�̃w�b�_
//!
//! @date   
//!
//! @author �ߓ��@�D�a
////////////////////////////////////////////////////////////////////////////



// ���d�C���N���[�h�h�~ -----------------------------------------------------
#pragma once



// �w�b�_�̓ǂݍ��� ---------------------------------------------------------
#include <SpriteBatch.h>
#include "..\Utility\ComHelper.h"



// --------------------------------------------------------------------------
// Sprite�N���X
// --------------------------------------------------------------------------
class Sprite
{
	//friend SpriteManager;
private:
	// �^ ------------------------------------------------------------------
	using Textue = Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>;
	using Color = DirectX::SimpleMath::Color;   
	using Vec2 = DirectX::SimpleMath::Vector2;

	// �����o�ϐ� ----------------------------------------------------------
private:
	std::unique_ptr < DirectX::SpriteBatch >	m_sprite;				// �X�v���C�g�o�b�`
	Textue										m_pTextue;				// �e�N�X�`��
	RECT										m_textureRegion;		// �e�N�X�`���̕`��͈�
	Color										m_color;				// �`��F
	Vec2										m_origin;				// ���_
	Vec2                                        m_scale;				// �k��
	float										m_rotationAngle;		// ��]�p



	// �R���X�g���N�^ ------------------------------------------------------
public:
	Sprite(Textue pTextue, RECT textureRegion);

	// �f�X�g���N�^
	~Sprite();


	//	�����o�֐� ---------------------------------------------------------
public:

	// �e�N�X�`���𓾂�
	Textue GetTextue() { return m_pTextue.Get(); };

	// �e�N�X�`���͈͂𓾂�
	RECT   GetTextueRegion() { return m_textureRegion; };

	// �e�N�X�`���͈͂�ݒ�
	void SetTextueRegion(RECT region) { m_textureRegion = region; };

	// ��]�p�̐ݒ�
	void SetRotationAngle(float rotationAngle);

	// �k�ڂ̐ݒ�
	void SetScale(float scale);

	// �k�ڂ̐ݒ�@XY�w��\
	void SetScale(float scaleX, float scaleY);

	// ���_�̐ݒ�
	void SetOrigin(const Vec2& origin);

	// �`��F�̐ݒ�
	void SetColor(const Color& color);

	// �`��F�̕W���ݒ�
	void Sprite::SetColor(const DirectX::XMVECTOR& color);

	// ���ߐF�̐ݒ�
	void SetAlpha(float alpha);

	// �`��
	void Draw(DirectX::SpriteBatch* spriteBatch, const Vec2& position);

};