////////////////////////////////////////////////////////////////////////////
//! @file   GameBase.h
//!
//! @brief  �Q�[���̊�{�N���X�̃w�b�_�t�@�C��
//!
//! @date   
//!
//! @author �ߓ��@�D�a
////////////////////////////////////////////////////////////////////////////

// ���d�C���N���[�h�h�~ 
#pragma once




// �w�b�_�t�@�C���̓ǂݍ��� 
#include <memory>
#include <string>

#include <Windows.h>

#include <d3d11.h>

#include "ScreenMode.h"




// �N���X�錾
class Window;
class Direct3D;
class FrameRateController;




// ---------------------------------------------------------------------------
// GameBase�N���X
// ---------------------------------------------------------------------------
class GameBase
{
	// �����o�ϐ� ----------------------------------------------
private:


	std::unique_ptr<Window>              m_pWindow;                 //!< �E�B���h�E
	std::unique_ptr<Direct3D>            m_pDirect3D;               //!< Direct3D

	std::unique_ptr<FrameRateController> m_pFrameRateController;    //!< �t���[�����[�g���䑕�u



	// �R���X�g���N�^ ------------------------------------------
public:
	GameBase();



	// �f�X�g���N�^ --------------------------------------------
public:
	virtual ~GameBase();



	// ���� ----------------------------------------------------
public:

	// �t���[�����[�g�̎擾
	double GetFrameRate() const;

	// �t���[�����[�g�̐ݒ�
	void SetFrameRate(int frameRate);



	// ���� ----------------------------------------------------
public:

	// �Q�[���̎��s
	int Run(ScreenMode screenMode);



	// �������� ------------------------------------------------
private:

	// �V�X�e���̏�����
	bool InitializeSystem();

	// ������
	virtual bool Initialize() = 0;

	// �X�V
	virtual void Update() = 0;

	// �`��
	virtual void Render() = 0;

	// ��n��
	virtual void Finalize() = 0;


};