// ���d�C���N���[�h�h�~
#pragma once

class Scene;


// �w�b�_�̓ǂݍ���



class ChangeScene
{

	// �����o�֐� ---------------------------------------------------------
public:

	// �������z�֐�
	virtual void SceneChange(Scene* currentScene) = 0;
};
