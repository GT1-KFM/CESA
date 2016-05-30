/////////////////////////////////////////////////////////////////////////////////
//! @file   GameBase.cpp
//!
//! @brief  �Q�[���̊�{�N���X�̃\�[�X�t�@�C��
//!
//! @date   2016/5/18
//!
//! @author �ߓ��D�a
////////////////////////////////////////////////////////////////////////////////

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "GameBase.h"
#include "..\System\Direct3D\Direct3D.h"
#include "..\System\FrameRateController\FrameRateController.h"
#include "..\System\Window\Window.h"
#include "..\Utility\ComHelper.h"



// ���O��Ԃ̎g�p�錾
using namespace std;




//------------------------------------------------------------------
//! @brief �R���X�g���N�^
//!
//! @param
//------------------------------------------------------------------
GameBase::GameBase()
	: m_pFrameRateController(nullptr)
{
}



//------------------------------------------------------------------
//! @brief �f�X�g���N�^
//------------------------------------------------------------------
GameBase::~GameBase()
{
}





//------------------------------------------------------------------
//! @brief �t���[�����[�g�̎擾
//!
//! @param �Ȃ�
//!
//! @return �t���[�����[�g
//------------------------------------------------------------------
double GameBase::GetFrameRate() const
{
	return m_pFrameRateController->GetFrameRate();
}



//------------------------------------------------------------------
//! @brief �t���[�����[�g�̐ݒ�
//!
//! @param[in] frameRate �t���[�����[�g
//!
//! @return �Ȃ�
//------------------------------------------------------------------
void GameBase::SetFrameRate(int frameRate)
{
	m_pFrameRateController->SetFrameRate(frameRate);
}




//-----------------------------------------------------------------
//! @brief �Q�[���̎��s
//!
//! @param[in] screenMode �N���X�N���[�����[�h
//!
//! @retval �I���R�[�h ���s����
//! @retval 0          ���s���s
//-----------------------------------------------------------------
int GameBase::Run(ScreenMode screenMode)
{
	// �V�X�e���̏�����
	if (!InitializeSystem())
	{
		return 0;
	}


	// �Q�[���̏�����
	if (!Initialize())
	{
		Finalize();
		return 0;
	}


	// �w��̃X�N���[�����[�h�ŋN��
	m_pDirect3D->SetFullscreenState(toBool(screenMode));


	// �t���[�����[�g�̌v���J�n
	m_pFrameRateController->Start();


	// ���b�Z�[�W���[�v
	while (m_pWindow->HandleMessage())
	{
		// �t���[�����[�g�̒���
		m_pFrameRateController->Adjust();


		// �Q�[���̍X�V
		Update();


		// �Q�[���̕`��
		if (!m_pFrameRateController->IsSkipFrame())
		{
			Render();
		}
	}


	// �Q�[���̌�n��
	Finalize();


	// �E�B���h�E�\�����[�h�Ɉڍs
	m_pDirect3D->SetFullscreenState(toBool(ScreenMode::WINDOWED));


	// �I���R�[�h�̕ԋp
	return m_pWindow->GetExitValue();
}



//-----------------------------------------------------------------
//! @brief �V�X�e���̏�����
//!
//! @param �Ȃ�
//!
//! @retval true  �V�X�e���̏������ɐ���
//! @retval false �V�X�e���̏������Ɏ��s
//-----------------------------------------------------------------
bool GameBase::InitializeSystem()
{
	// �E�B���h�E�̍쐬
	m_pWindow.reset(Window::GetInstance());
	if (!m_pWindow)
	{
		MessageBox(nullptr, L"�E�B���h�E�̍쐬�Ɏ��s���܂����B", L"Error [Game]", MB_OK);
		return false;
	}

	// Direct3D�f�o�C�X�̍쐬
	m_pDirect3D.reset(Direct3D::GetInstance());
	if (!m_pDirect3D)
	{
		MessageBox(nullptr, L"Direct3D���̍\�z�Ɏ��s���܂����B", L"Error [Game]", MB_OK);
		return false;
	}


	// �t���[�����[�g���䑕�u�̍쐬
	m_pFrameRateController = make_unique<FrameRateController>();




	// �V�X�e���̏������ɐ���
	return true;
}