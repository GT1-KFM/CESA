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

	// �X�V
	virtual void Update(ChangeScene* pChangeScene) = 0;

	// �`��
	virtual void Render() = 0;

};