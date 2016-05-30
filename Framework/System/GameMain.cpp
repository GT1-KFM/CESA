////////////////////////////////////////////////////////////////////
//! @file   GameMain.coo
//!
//! @brief  �Q�[���̔h���N���X�̃\�[�X�t�@�C��
//!
//! @date   2016/5/25
//!
//! @author �ߓ��@�D�a
////////////////////////////////////////////////////////////////////


// �w�b�_�t�@�C���̓ǂݍ��� ----------------------------------------
#include <WICTextureLoader.h>

#include "GameMain.h"
#include "..\System\Direct3D\direct3d.h"
#include "..\System\Window\Window.h"
#include "..\Utility\CommonStates\CommonStatesHelper.h"
#include "..\Scene\MyScene\TitleScene.h"
#include "..\Graphics\SpriteManager.h"
#include "..\Input\InputManager.h"
#include "..\System\Direct3D\Direct3D.h"


// ���O��Ԃ̎g�p�錾 ----------------------------------------------
using namespace std;
using namespace DirectX;




//------------------------------------------------------------------
//! @brief �R���X�g���N�^
//------------------------------------------------------------------
GameMain::GameMain()
	: GameBase()
{
}



//------------------------------------------------------------------
//! @brief �f�X�g���N�^
//------------------------------------------------------------------
GameMain::~GameMain()
{

}



//------------------------------------------------------------------
//! @brief �Q�[���̏�����
//!
//! @param �Ȃ�
//!
//! @retval true  �������ɐ���
//! @retval false �������Ɏ��s
//------------------------------------------------------------------
bool GameMain::Initialize()
{
	// �t���[�����[�g�̐ݒ�(60FPS)
	SetFrameRate(60);

	// �V�[���}�l�[�W���̐���
	m_pSceneManager.reset(SceneManager::GetInstance());

	// ���߂̃V�[����ݒ肷��
	m_pSceneManager->SceneChange(TitleScene::GetInstance());

	InputManager::GetInstance()->OnKeyboard();


	// �������ɐ���
	return true;
}




//------------------------------------------------------------------
//! @brief �Q�[���̍X�V
//!
//! @param �Ȃ�
//!
//! @return �Ȃ�
//------------------------------------------------------------------
void GameMain::Update()
{
	// �V�[���}�l�[�W���̍X�V
	m_pSceneManager->Update();

}



//------------------------------------------------------------------
//! @brief �Q�[���̕`��
//!
//! @param �Ȃ�
//!
//! @return �Ȃ�
//------------------------------------------------------------------
void GameMain::Render()
{
	// �_�C���N�g3D�̎擾
	Direct3D* direct3D = Direct3D::GetInstance();

	// �f�o�C�X���\�[�X�̎擾
	ID3D11DeviceContext*    pDeviceContext = direct3D->GetDeviceContext();
	ID3D11RenderTargetView* pRenderTargetView = direct3D->GetRenderTargetView();

	//�[�x�o�b�t�@�̎擾
	ID3D11DepthStencilView*  pDepthStencilView = direct3D->GetDepthStencilView();
	IDXGISwapChain*         pSwapChain = direct3D->GetSwapChain();
	

	// �����_�[�^�[�Q�b�g�̃N���A
	pDeviceContext->ClearRenderTargetView(pRenderTargetView, Colors::DarkBlue);
	//�[�x�o�b�t�@�̃N���A
	pDeviceContext->ClearDepthStencilView(pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);


	// �V�[���}�l�[�W���̕`��
	m_pSceneManager->Render();


	// ��ʂ̃t���b�v
	pSwapChain->Present(0, 0);


}



//------------------------------------------------------------------
//! @brief �Q�[���̌�n��
//!
//! @param �Ȃ�
//!
//! @return �Ȃ�
//------------------------------------------------------------------
void GameMain::Finalize()
{
	m_pSceneManager->Finalize();
	CommonStatesHelper::Dispose();
	InputManager::Dispose();
}