////////////////////////////////////////////////////////////////////////////
//! @file   PlayScene.cpp
//!
//! @brief  �v���C�V�[���̃\�[�X�t�@�C��
//!
//! @date   2016/05/25
//!
//! @author �ߓ��@�D�a
////////////////////////////////////////////////////////////////////////////


// �w�b�_�t�@�C���̓ǂݍ��� ------------------------------------------------
#include "PlayScene.h"
#include "TitleScene.h"
#include "..\SceneManager.h"
#include "Framework\Input\InputManager.h"
#include "Framework\Graphics\Obj3D.h"
#include "Framework\System\Direct3D\Direct3D.h"
#include "Framework\Utility\CommonStates\CommonStatesHelper.h"
#include "Framework\System\Window\Window.h"


// ���O��Ԃ̎g�p�錾 ------------------------------------------------------
using namespace std;
using namespace DirectX;


// �ÓI�����o�ϐ��̎��� ----------------------------------------------------
Scene* PlayScene::pScene = nullptr;


// -------------------------------------------------------------------------
//! @brief     �R���X�g���N�^
// -------------------------------------------------------------------------
 PlayScene::PlayScene()
{
	this->Initialize();
}




 // ------------------------------------------------------------------------
 //! @brief     �f�X�g���N�^
 // ------------------------------------------------------------------------
 PlayScene::~PlayScene()
 {
 }





// -------------------------------------------------------------------------
//! @brief     ������
// -------------------------------------------------------------------------
void PlayScene::Initialize()
{



}


// -------------------------------------------------------------------------
//! @brief      �X�V
//!
//! @param[in]	�`�F���W�V�[��
// -------------------------------------------------------------------------
void PlayScene::Update(ChangeScene* pChangeScene)
{

	auto inputManager = InputManager::GetInstance();
	inputManager->Update();


	//<! �e�X�g
	// �@�V�[����؂�ւ���@
	if (inputManager->GetKeyboard()->IsKeyDown(VK_SPACE))
	{
		pChangeScene->SceneChange(TitleScene::GetInstance());
	}

}

// -------------------------------------------------------------------------
//! @brief      �`��
// -------------------------------------------------------------------------
void PlayScene::Render()
{

	
}






// -------------------------------------------------------------------------
// �I�u�W�F�N�g��j��
//--------------------------------------------------------------------------
void PlayScene::Dispose()
{
	if (pScene != nullptr)
		delete pScene;
}



