////////////////////////////////////////////////////////////////////////////
//! @file   FadeScene.h
//!
//! @brief  �^�C�g���V�[���̃w�b�_�t�@�C��
//!
//! @date   2016/05/24
//!
//! @author �ߓ��@�D�a
////////////////////////////////////////////////////////////////////////////


// ���d�C���N���[�h�h�~ ---------------------------------------------------
#pragma once

// �w�b�_�̓ǂݍ��� -------------------------------------------------------
#include "..\Scene.h"
#include "Framework\Graphics\SpriteManager.h"




// ---------------------------------------------------------------------------
// FadeScene�N���X
// ---------------------------------------------------------------------------
class FadeScene
{
	// �ÓI�����o�ϐ� --------------------------------------------------------
private:





	// �����o�ϐ� ------------------------------------------------------------
private:

	static FadeScene*						m_pFadeScene;				// �V�[���i�[�p
	std::unique_ptr<SpriteManager>			m_pSpriteManager;   // �X�v���C�g�}�l�[�W��
	std::unique_ptr<Sprite>					m_pFadeSprite;		// �t�F�[�h�p�X�v���C�g
	float									m_alpha;


	// �R���X�g���N�^ ---------------------------------------------------------
public:

	FadeScene();


	// �f�X�g���N�^ -----------------------------------------------------------
public:

	virtual ~FadeScene();



	//	�����o�֐� ------------------------------------------------------------
public:


	//-------------------------------------------------------------------------
	//! @brief �t�F�[�h�ւ̃A�h���X���擾����
	//!
	//! @param �Ȃ�
	//!
	//! @retval pScene
	//-------------------------------------------------------------------------
	static FadeScene* GetInstance()
	{
		if (m_pFadeScene == nullptr)
			m_pFadeScene = new FadeScene();
		return m_pFadeScene;
	}


	// ������
	void Initialize();
	
	// �X�V
	void Update();

	// �`��
	void Render();

	// �t�F�[�h�̃��Z�b�g
	void Reset() { m_alpha = 1.0f; };

	// �I�u�W�F�N�g�̔j��
	static void Dispose();

};
#pragma once
