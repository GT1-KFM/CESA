////////////////////////////////////////////////////////////////////////////
//! @file   WinMain.cpp
//!
//! @brief  WinMain�̃\�[�X�t�@�C��
//!
//! @date   2016/5/18
//!
//! @author �ߓ��@�D�a
////////////////////////////////////////////////////////////////////////////

// �C���N���[�h�̓ǂݍ���
#include <windows.h>
#include "ScreenMode.h"
#include <memory>
#include "GameBase.h"
#include "GameMain.h"
#include "..\Utility\MemoryLeakDetector.h"



// ���O��Ԃ̎g�p�錾
using namespace std;


//----------------------------------------------------------------------
//! @brief �v���O�����̃G���g���[�|�C���g
//!
//! @param[in] hInstance     ���݂̃C���X�^���X�̃n���h��
//! @param[in] hPrevInstance �ȑO�̃C���X�^���X�̃n���h��(���nullptr)
//! @param[in] lpCmdLine     �R�}���h���C��
//! @param[in] nCmdShow      �E�B���h�E�̕\�����
//!
//! @retval �I���R�[�h ����I��
//! @retval 0          �ُ�I��
//----------------------------------------------------------------------
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	// ���g�p�����̌x���΍�
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(nCmdShow);


#if defined(_DEBUG)
	// �������[���[�N���o�@�\�̃Z�b�g�A�b�v
	SetUpMemoryLeakDetector();
#endif

	// �X�N���[�����[�h�̐ݒ�
	ScreenMode screenMode = ScreenMode::WINDOWED;

	// �t���X�N���[���̉�
	if (MessageBox(nullptr, L"�t���X�N���[�����[�h�ŋN�����܂����H", L"��ʐݒ�", MB_OKCANCEL) == IDOK)
	{
		screenMode = ScreenMode::FULLSCREEN;
	}

	// �Q�[���̍쐬
	unique_ptr<GameBase> game = make_unique<GameMain>();

	// �Q�[���̎��s
	return game->Run(screenMode);

}