////////////////////////////////////////////////////////////////////////////
//! @file   TitleScene.cpp
//!
//! @brief  �^�C�g���V�[���̃\�[�X�t�@�C��
//!
//! @date   2016/05/23
//!
//! @author �ߓ��@�D�a
////////////////////////////////////////////////////////////////////////////


// �w�b�_�t�@�C���̓ǂݍ��� ----------------------------------------
#include "TitleScene.h"
#include "PlayScene.h"


// ���O��Ԃ̎g�p�錾 ----------------------------------------------
using namespace std;
using namespace DirectX;
using namespace SimpleMath;




// �ÓI�����o�ϐ��̒�` --------------------------------------------
const wchar_t* TitleScene::TITLE_PATH = L"Scene/Title.png";
Scene* TitleScene::pScene = nullptr;




//------------------------------------------------------------------
//! @brief �R���X�g���N�^
//------------------------------------------------------------------
TitleScene::TitleScene()
{
	this->Initialize();
}





//------------------------------------------------------------------
//! @brief �f�X�g���N�^
//------------------------------------------------------------------
TitleScene::~TitleScene()
{

}






//------------------------------------------------------------------
//! @brief �Q�[���̏�����
//!
//! @param �Ȃ�
//!
//! @retval �Ȃ�
//------------------------------------------------------------------
void TitleScene::Initialize()
{

	// �X�v���C�g�}�l�[�W��
	m_pSpriteManager.reset(SpriteManager::GetInstance());

	// �^�C�g���X�v���C�g�̐���
	m_pTitleSprite.reset(m_pSpriteManager->CreateSprite(TITLE_PATH));


}


//------------------------------------------------------------------
//! @brief		�X�V
//!
//! @param[in]	ChangeScene*	�`�F���W�V�[��
//!
//! @retval		�Ȃ�
//------------------------------------------------------------------
void TitleScene::Update(ChangeScene* pChangeScene)
{
	//pChangeScene->SceneChange(PlayScene::GetInstance());

}




//------------------------------------------------------------------
//! @brief		�`��
//!
//! @param		�Ȃ�
//!
//! @retval		�Ȃ�
//------------------------------------------------------------------
void TitleScene::Render()
{
	m_pSpriteManager->Render(m_pTitleSprite.get(), Vector2(0.0f, 0.0f));
}





//------------------------------------------------------------------
//! @brief		�I�u�W�F�N�g�̔j��
//!
//! @param[in]	�Ȃ�
//!
//! @retval		�Ȃ�
//------------------------------------------------------------------
void TitleScene::Dispose()
{
	if (pScene != nullptr)
		delete pScene;
}