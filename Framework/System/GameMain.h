////////////////////////////////////////////////////////////////////////////
//! @file   GameMain.h
//!
//! @brief  �Q�[���̔h���N���X�̃w�b�_�t�@�C��
//!
//! @date   2016/5/19
//!
//! @author �ߓ��@�D�a
////////////////////////////////////////////////////////////////////////////


// ���d�C���N���[�h�h�~ 
#pragma once




// �w�b�_�t�@�C���̓ǂݍ��� 
#include "..\System\GameBase.h"
#include<CommonStates.h>
#include"Effects.h"
#include "Model.h"
#include "..\Input\InputManager.h"
#include "..\Graphics\SpriteManager.h"	
#include "..\Scene\SceneManager.h"
#include "Framework\Camera\Camera.h"


// ---------------------------------------------------------------------------
// GameMain�N���X
// ---------------------------------------------------------------------------
class GameMain : public GameBase
{
	static const int ENEMY_NUM = 1;



	// �����o�ϐ� ----------------------------------------------
private:

	std::unique_ptr<SceneManager>	m_pSceneManager;	// �V�[���}�l�[�W��
	std::unique_ptr<Camera>			m_pCamera;			// �J����



	// �R���X�g���N�^ ------------------------------------------
public:
	GameMain();



	// �f�X�g���N�^ --------------------------------------------
public:
	~GameMain();



	// ���� ----------------------------------------------------
public:
	// ������
	bool Initialize();

	// �X�V
	void Update();

	// �`��
	void Render();

	// ��n��
	void Finalize();
};
