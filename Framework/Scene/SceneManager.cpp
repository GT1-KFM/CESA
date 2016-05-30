////////////////////////////////////////////////////////////////////////////
//! @file   SceneManager.cpp
//!
//! @brief  �V�[���}�l�[�W���̃\�[�X�t�@�C��
//!
//! @date   2016/5/25
//!
//! @author �ߓ��@�D�a
////////////////////////////////////////////////////////////////////////////


// �w�b�_�t�@�C���̓ǂݍ��� -------------------------------------------------
#include "SceneManager.h"
using namespace DirectX;
using namespace SimpleMath;


// ���O��Ԃ̎g�p�錾 -------------------------------------------------------
using namespace std;



// �ÓI�����o�ϐ��̎��̂�錾------------------------------------------------
SceneManager* SceneManager::m_pSceneManager = nullptr;
const wchar_t* SceneManager::FADE_DISPLAY = L"Scene/BlackDisplay.png";
const float	SceneManager::FADE_ALPHA_MAX = 2.0f;
const float	SceneManager::FADE_ALPHA_MIN = 0.0f;
const float SceneManager::FADE_SPPED = 0.1f;






// ---------------------------------------------------------------------------
//! @brief     �R���X�g���N�^
// ---------------------------------------------------------------------------
SceneManager::SceneManager()
{
	this->Initialize();
}




// ---------------------------------------------------------------------------
//! @brief     �f�X�g���N�^
// ---------------------------------------------------------------------------
SceneManager::~SceneManager()
{

}





// ---------------------------------------------------------------------------
//! @brief      ������
// ---------------------------------------------------------------------------
void SceneManager::Initialize()
{
	// �X�v���C�g�}�l�[�W��
	m_pSpriteManager.reset(SpriteManager::GetInstance());

	// ���݂̃V�[����������
	m_pCurrentScene = nullptr;

	//�t�F�[�h�p�摜
	m_pFadeSprite.reset(m_pSpriteManager->CreateSprite(FADE_DISPLAY));
	//���ߐF��ݒ�
	m_alpha = 1.0f;

	// ���̃V�[����������
	m_pNextScene = nullptr;

	// �t�F�[�h�t���O���I�t
	m_fadeInFlag = false;
	m_fadeOutFlag = false;
}





// ---------------------------------------------------------------------------
//! @brief      �X�V
// ---------------------------------------------------------------------------
void SceneManager::Update()
{
	// �V�[�����X�V
	m_pCurrentScene->Update(this);

	// �t�F�[�h�����s
	this->FadeOut();
	this->FadeIn();

}




// ---------------------------------------------------------------------------
//! @brief      �`��
// ---------------------------------------------------------------------------
void SceneManager::Render()
{
	m_pCurrentScene->Render();

	// �t�F�[�h��`��
	if (m_fadeInFlag || m_fadeOutFlag)
	{
		m_pSpriteManager->Render(m_pFadeSprite.get(), Vector2(0.0f, 0.0f));
	}

}





// ---------------------------------------------------------------------------
//! @brief      ��n��
// ---------------------------------------------------------------------------
void SceneManager::Finalize()
{
	TitleScene::Dispose();
	PlayScene::Dispose();
}




// ---------------------------------------------------------------------------
//! @brief      �t�F�[�h�C��
// ---------------------------------------------------------------------------
void SceneManager::FadeIn()
{
	if (m_alpha >= FADE_ALPHA_MIN && m_fadeInFlag)
	{
		m_pFadeSprite->SetAlpha(m_alpha);
		m_alpha -= FADE_SPPED;
	}
	// �t�F�[�h���I�����Ă����ꍇ�t���O���I�t
	else if (m_alpha <= FADE_ALPHA_MIN)
	{
		m_fadeInFlag = false;
	}
}






// ---------------------------------------------------------------------------
//! @brief      �t�F�[�h�A�E�g
// ---------------------------------------------------------------------------
void SceneManager::FadeOut()
{
	if (m_alpha <= FADE_ALPHA_MAX && m_fadeOutFlag)
	{
		m_alpha += FADE_SPPED;
		m_pFadeSprite->SetAlpha(m_alpha);
	}
	// �t�F�[�h���I�����Ă����ꍇ�t���O���I�t
	else if(m_alpha >= FADE_ALPHA_MAX)
	{
		m_fadeOutFlag = false;
		m_fadeInFlag = true;
		m_pCurrentScene = m_pNextScene;
	}
}






// ---------------------------------------------------------------------------
//! @brief      �V�[���̕ύX
// ---------------------------------------------------------------------------
void SceneManager::SceneChange(Scene* currentScene)
{
	// ��ԏ��߂̃V�[��
	if (m_pNextScene == nullptr)
	{
		m_pCurrentScene = currentScene;
		m_pNextScene = m_pCurrentScene;
		return;
	}

	if (currentScene != m_pNextScene)
	{
		m_alpha = FADE_ALPHA_MIN;
		m_pNextScene = currentScene;
		m_fadeOutFlag = true;
		m_fadeInFlag = false;
	}
}