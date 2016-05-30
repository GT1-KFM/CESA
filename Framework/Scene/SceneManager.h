////////////////////////////////////////////////////////////////////////////
//! @file   SceneManager.h
//!
//! @brief  �V�[���}�l�[�W���̃w�b�_�t�@�C��
//!
//! @date   2016/5/24
//!
//! @author �ߓ��@�D�a
////////////////////////////////////////////////////////////////////////////


// ���d�C���N���[�h�h�~ ---------------------------------------------------
#pragma once



// �w�b�_�t�@�C���̓ǂݍ��� ------------------------------------------------
#include "Scene.h"
#include <string>
#include "ChangeScene.h"
#include "MyScene\TitleScene.h"
#include "MyScene\PlayScene.h"
#include "Framework\Graphics\SpriteManager.h"



// ---------------------------------------------------------------------------
// SceneManager�N���X
// ---------------------------------------------------------------------------
class SceneManager	: public ChangeScene
{

	// �ÓI�����o�ϐ� -----------------------------------------------------
private:

	static SceneManager*			m_pSceneManager;		// SceneManager
	static const wchar_t*			FADE_DISPLAY;			// �t�F�[�h�p�摜�p�X
	static const float			FADE_ALPHA_MAX;			// �t�F�[�h����ő厞��
	static const float			FADE_ALPHA_MIN;			// �t�F�[�h����ŏ����ԁ@
	static const float			FADE_SPPED;				// �t�F�[�h�̃X�s�[�h

	// �����o�ϐ� ---------------------------------------------------------
private:
	
	Scene*							m_pCurrentScene;		// ���݂̃V�[��
	Scene*							m_pNextScene;			// ���̃V�[��
	std::unique_ptr<SpriteManager>	m_pSpriteManager;	// �X�v���C�g�}�l�[�W��
	std::unique_ptr<Sprite>			m_pFadeSprite;			// �t�F�[�h�p�X�v���C�g
	bool							m_fadeInFlag;			// �t�F�[�h�C���̃^�C�~���O
	bool							m_fadeOutFlag;			// �t�F�[�h�A�E�g�̃^�C�~���O
	float							m_alpha;				// ���ߐF


	// �R���X�g���N�^ ---------------------------------------------------------
private:

	SceneManager();


	// �f�X�g���N�^ -----------------------------------------------------------
public:

	 ~SceneManager();


	// �ÓI�����o�֐� ---------------------------------------------------------
public:


	// ---------------------------------------------------------------------------
	//! @brief      �V�[���}�l�[�W���ւ̃A�h���X���擾����
	//
	//! @param		�Ȃ�
	//!
	//! @return     pSceneManager
	// ---------------------------------------------------------------------------
	static SceneManager* GetInstance()
	{
		// ��̏ꍇSceneManager�𐶐�����
		if (m_pSceneManager == nullptr)
			m_pSceneManager = new SceneManager();

		return m_pSceneManager;
	}

	// �����o�֐� -------------------------------------------------------------
public:

	// ������
	void Initialize();

	// �X�V
	void Update();

	// �`��
	void Render();

	// ��n��
	void Finalize();

	//
	void FadeIn();

	//
	void FadeOut();

	// �V�[���̕ύX
	void SceneChange(Scene* currentScene) override;

};
