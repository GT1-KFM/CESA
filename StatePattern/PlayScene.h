// ���d�C���N���[�h�h�~
#pragma once

// �w�b�_�̓ǂݍ���
#include "Scene.h"


#define TO_STRING(VariableName) # VariableName



// ---------------------------------------------------------------------------
// PlayScene�N���X
// ---------------------------------------------------------------------------
class PlayScene : public Scene
{

	// �����o�ϐ� ------------------------------------------------------------
private:


	static Scene*							pScene;					// �V�[���i�[�p


	//	�����o�֐� ----------------------------------------------------------
public:

	// ������
	void Initialize();

	// �X�V
	void Update();

	// �`��
	void Render();

private:


public:
	// �C���X�^���X�̎擾
	static Scene* GetInstance();

	// ���s
	void Execute(ChangeScene* pChangeScene);


	// �I�u�W�F�N�g�̔j��
	static void Dispose();

};

