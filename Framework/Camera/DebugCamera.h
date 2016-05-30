
// ���d�C���N���[�h�h�~ 
#pragma once 

// �w�b�_�t�@�C���̓ǂݍ���
#include <SimpleMath.h>
#include"Framework\Input\InputManager.h"
#include "..\Graphics\Obj3D.h"
#include "Game\Collision\CollisionNode.h"

// ---------------------------------------------------------------------------
// DebugCamera�N���X
// ---------------------------------------------------------------------------
class DebugCamera //: public Charactor
{
	
	//	�����o�֐� --------------------------------------------------------
public:

	// �R���X�g���N�^
	DebugCamera();
	// �f�X�g���N�^
	~DebugCamera();

	// ������
	void Initialize();

	// �X�V
	void Update();

	// �s��̌v�Z
	void Calc();

	// �`��
	void Render();

	// �㏈��
	void Finalize();

	// �Z�b�^�[ -----------------------------------------------------------

	// ���W���擾
	const DirectX::SimpleMath::Vector3& GetTrans();
	// ���W��ݒ�
	void SetTrans(const DirectX::SimpleMath::Vector3& trans);
	// ��]�����擾
	const DirectX::SimpleMath::Vector3& GetRot();
	// ��]����ݒ�
	void SetRot(const DirectX::SimpleMath::Vector3& rot);
	// ���[���h�s����擾
	const DirectX::SimpleMath::Matrix& GetLocalWorld();
	// ���̓}�l�[�W����ݒ�


protected:
	// �����o�ϐ�

	Obj3D m_ObjDebugCamera;					// ���O�̃I�u�W�F�N�g



	//int 

	SphereNode m_CollisionNodeCamera;				// �s�������蔻��


};



