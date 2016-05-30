////////////////////////////////////////////////////////////////////////////
//! @file   TitleScene.h
//!
//! @brief  �^�C�g���V�[���̃w�b�_�t�@�C��
//!
//! @date   2016/05/24
//!
//! @author �ߓ��@�D�a
////////////////////////////////////////////////////////////////////////////

// ���d�C���N���[�h�h�~ -----------------------------------------------------
#pragma once



// �w�b�_�̓ǂݍ��� ---------------------------------------------------------
#include "..\Scene.h"
#include "Framework\Graphics\SpriteManager.h"
#include "..\ChangeScene.h"




// ---------------------------------------------------------------------------
// TitleScene�N���X
// ---------------------------------------------------------------------------
class TitleScene : public Scene
{
	// �ÓI�����o�ϐ� --------------------------------------------------------
private:

	static const wchar_t* TITLE_PATH;		// �^�C�g���摜�̃p�X



	// �����o�ϐ� ------------------------------------------------------------
private:
	
	static Scene*							pScene;				// �V�[���i�[�p
	SpriteManager*							m_pSpriteManager;
	std::shared_ptr<Sprite>					m_pTitleSprite;

	// �R���X�g���N�^ ---------------------------------------------------------
private:

	TitleScene();


	// �f�X�g���N�^ -----------------------------------------------------------
private:

	virtual ~TitleScene();



	//	�ÓI�����o�֐� --------------------------------------------------------
public:


	//-------------------------------------------------------------------------
	//! @brief �^�C�g���V�[���̃A�h���X���擾����
	//!
	//! @param �Ȃ�
	//!
	//! @retval pScene
	//-------------------------------------------------------------------------
	static Scene* GetInstance()
	{
		if (pScene == nullptr)
			pScene = new TitleScene();
		return pScene;
	}

	// �I�u�W�F�N�g�̔j��
	static void Dispose();


	//	�����o�֐� --------------------------------------------------------
public:

	// ������
	void Initialize();

	// �X�V
	void Update(ChangeScene* pChangeScene)override;

	// �`��
	void Render()override;

};
