// ���d�C���N���[�h�h�~
#pragma once

// �w�b�_�̓ǂݍ���
#include "Scene.h"


// ---------------------------------------------------------------------------
// TitleScene�N���X
// ---------------------------------------------------------------------------
class TitleScene : public Scene
{

	// �����o�ϐ� --------------------------------------------------------
private:

	
	static Scene*							pScene;					// �V�[���i�[�p


	//	�����o�֐� --------------------------------------------------------
public:

	// ������
	void Initialize();

	// �X�V
	void Update(ChangeScene* pChangeScene);

	// �`��
	void Render();

	// �C���X�^���X�̎擾
	static Scene* GetInstance();

	// �I�u�W�F�N�g�̔j��
	static void Dispose();

};
