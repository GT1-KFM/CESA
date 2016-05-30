////////////////////////////////////////////////////////////////////////////
//! @file   TitleScene.cpp
//!
//! @brief  �^�C�g���V�[���̃\�[�X�t�@�C��
//!
//! @date   2016/05/27
//!
//! @author �ߓ��@�D�a
////////////////////////////////////////////////////////////////////////////


// �w�b�_�t�@�C���̓ǂݍ��� ----------------------------------------
#include "TitleScene.h"
#include "PlayScene.h"
#include "Framework\Input\InputManager.h"



// ���O��Ԃ̎g�p�錾 ----------------------------------------------
using namespace std;
using namespace DirectX;
using namespace SimpleMath;




// �ÓI�����o�ϐ��̒�` --------------------------------------------
Scene* TitleScene::pScene = nullptr;
const wchar_t* TitleScene::TITLE_PATH = L"Scene/Title.png";




//------------------------------------------------------------------
//! @brief		�R���X�g���N�^
//------------------------------------------------------------------
TitleScene::TitleScene()
{
	this->Initialize();
}





//------------------------------------------------------------------
//! @brief		�f�X�g���N�^
//------------------------------------------------------------------
TitleScene::~TitleScene()
{

}






//------------------------------------------------------------------
//! @brief		�Q�[���̏�����
//------------------------------------------------------------------
void TitleScene::Initialize()
{

	// �X�v���C�g�}�l�[�W��
	auto sprite = SpriteManager::GetInstance();


	// �^�C�g���X�v���C�g�̐���
	m_pTitleSprite.reset(sprite->CreateSprite(TITLE_PATH));



}


//------------------------------------------------------------------
//! @brief		�X�V
//!
//! @param[in]	ChangeScene*	�V�[���̕ύX
//------------------------------------------------------------------
void TitleScene::Update(ChangeScene* pChangeScene)
{
	auto inputManager = InputManager::GetInstance();



	if (inputManager->GetKeyboard()->IsKeyDown(VK_SPACE))
	{
		pChangeScene->SceneChange(PlayScene::GetInstance());

	}

	inputManager->Update();
}




//------------------------------------------------------------------
//! @brief		�`��
//------------------------------------------------------------------
void TitleScene::Render()
{
	auto sprite = SpriteManager::GetInstance();

	SpriteManager::GetInstance()->Render(m_pTitleSprite.get(), Vector2(0.0f, 0.0f));
}





//------------------------------------------------------------------
//! @brief		�I�u�W�F�N�g�̔j��
//------------------------------------------------------------------
void TitleScene::Dispose()
{
	if (pScene != nullptr)
		delete pScene;
	
}