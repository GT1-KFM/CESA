// ���d�C���N���[�h�h�~
#pragma once



// �w�b�_�t�@�C���̓ǂݍ���
#include "Scene.h"
#include <map>
#include <string>
#include "ChangeScene.h"



// �N���X��`
class SceneManager	: public ChangeScene
{

	// �����o�ϐ� ---------------------------------------------------------
private:

	Scene*									pCurrentScene;			// ���݂̃V�[��

	// �����o�֐� ---------------------------------------------------------
public:

	// �R���X�g���N�^
	SceneManager();


	// �f�X�g���N�^
	~SceneManager();


	// �V�[����ύX����
	void SceneChange(Scene* currentScene);

	// ������
	void Initialize();

	// �X�V

	void Update();

	// �`��
	void Render();

	// �㏈��
	void Finalize();


};
