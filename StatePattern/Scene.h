// ���d�C���N���[�h�h�~
#pragma once

// �O���錾
class ChangeScene;

// �N���X�錾
class Scene
{


	// �����o�֐� --------------------------------------------------------
public:


	// ���z�f�X�g���N�^
	virtual ~Scene() {}

	// �������z�֐�
	virtual void Execute(ChangeScene* pChangeScene) = 0;

};