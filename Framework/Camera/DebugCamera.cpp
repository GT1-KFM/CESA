// �w�b�_�t�@�C���̓ǂݍ���
#include "DebugCamera.h"
#include "Game\Collision\Collision.h"
#include "..\Input\InputManager.h"

// �l�[���X�y�[�X
using namespace DirectX;
using namespace DirectX::SimpleMath;




// ---------------------------------------------------------------------------
// �R���X�g���N�^
//----------------------------------------------------------------------------
DebugCamera::DebugCamera()
//	:Charactor()
{
}




// ---------------------------------------------------------------------------
// �f�X�g���N�^
//----------------------------------------------------------------------------
DebugCamera::~DebugCamera()
{
}




//-----------------------------------------------------------------------------
// ������
//-----------------------------------------------------------------------------
void DebugCamera::Initialize()
{
	// �f�o�b�O�J����
	//m_ObjDebugCamera.LoadModelFile(L"Resources/cModels/ball.cmo");
	m_ObjDebugCamera.LoadModelFile(L"Resources/cModels/LockBase.cmo");

	
	// �s���̂����蔻��̐ݒ�
	// ������
	m_CollisionNodeCamera.Initialize();
	// �e�̐ݒ�
	m_CollisionNodeCamera.SetParentMatrix(&m_ObjDebugCamera.GetLocalWorld());
	// ���[�J�����a
	m_CollisionNodeCamera.SetLocalRadius(0.05f);
	// ���[�J���̍���
	m_CollisionNodeCamera.SetLength(0.1f);
	// �e����̋���
	m_CollisionNodeCamera.SetTrans(Vector3(0.0f, 0.05f, 0.0f));

}



//-----------------------------------------------------------------------------
// �X�V
//-----------------------------------------------------------------------------
void DebugCamera::Update()
{
	// �P�t���[���ł̐��񑬓x<���W�A��>
	const float ROT_SPEED = 0.05f;
	const float MOVE_SPEED = 0.05f;

	auto input = InputManager::GetInstance();

	//-------------------------------------------------------------------
	// ���s�ړ�

	// �O�i
	if (input->GetKeyboard()->IsKeyDown('W'))
	{
		SimpleMath::Vector3 trans = m_ObjDebugCamera.GetTrans();
		const SimpleMath::Vector3& rot = m_ObjDebugCamera.GetRot();

		//�ړ��x�N�g��(W���W�O�i)
		SimpleMath::Vector3 moveV(0, 0, 0.1f);
		SimpleMath::Matrix rotmat = SimpleMath::Matrix::CreateRotationY(rot.y);
		moveV = SimpleMath::Vector3::Transform(moveV, rotmat);
		//���@�̍��W���ړ�
		trans += moveV;

		// ���f������
		m_ObjDebugCamera.SetTrans(trans);
	}
	// ���
	if (input->GetKeyboard()->IsKeyDown('S'))
	{
		SimpleMath::Vector3 trans = m_ObjDebugCamera.GetTrans();
		const SimpleMath::Vector3& rot = m_ObjDebugCamera.GetRot();

		//�ړ��x�N�g��(W���W�O�i)
		SimpleMath::Vector3 moveV(0, 0, 0.1f);
		SimpleMath::Matrix rotmat = SimpleMath::Matrix::CreateRotationY(rot.y);
		moveV = SimpleMath::Vector3::Transform(moveV, rotmat);
		//���@�̍��W���ړ�
		trans -= moveV;

		// ���f������
		m_ObjDebugCamera.SetTrans(trans);
	}

	// �E�i
	if (input->GetKeyboard()->IsKeyDown('A'))
	{
		SimpleMath::Vector3 trans = m_ObjDebugCamera.GetTrans();
		const SimpleMath::Vector3& rot = m_ObjDebugCamera.GetRot();

		//�ړ��x�N�g��(W���W�O�i)
		SimpleMath::Vector3 moveV(-0.01f, 0.0f, 0.0f);
		SimpleMath::Matrix rotmat = SimpleMath::Matrix::CreateRotationY(rot.y);
		moveV = SimpleMath::Vector3::Transform(moveV, rotmat);
		//���@�̍��W���ړ�
		trans -= moveV;

		// ���f������
		m_ObjDebugCamera.SetTrans(trans);
	}
	// ���i
	if (input->GetKeyboard()->IsKeyDown('D'))
	{
		SimpleMath::Vector3 trans = m_ObjDebugCamera.GetTrans();
		const SimpleMath::Vector3& rot = m_ObjDebugCamera.GetRot();

		//�ړ��x�N�g��(W���W�O�i)
		SimpleMath::Vector3 moveV(0.01f, 0.0f, 0.0f);
		SimpleMath::Matrix rotmat = SimpleMath::Matrix::CreateRotationY(rot.y);
		moveV = SimpleMath::Vector3::Transform(moveV, rotmat);
		//���@�̍��W���ړ�
		trans -= moveV;

		// ���f������
		m_ObjDebugCamera.SetTrans(trans);
	}


	//--------------------------------------------------------------------------
	// ��]
	// ����]
	if (input->GetKeyboard()->IsKeyDown('Q'))
	{
		m_ObjDebugCamera.SetQuternion(false);
		//��]�x�N�g��
		Vector3 rot = m_ObjDebugCamera.GetRot();
		float plus = rot.y += ROT_SPEED;

		m_ObjDebugCamera.SetRot(Vector3(0, plus, 0));


	}
	// 
	if (input->GetKeyboard()->IsKeyDown('E'))
	{
		m_ObjDebugCamera.SetQuternion(false);
		//��]�x�N�g��
		Vector3 rot = m_ObjDebugCamera.GetRot();
		float plus = rot.y -= ROT_SPEED;

		m_ObjDebugCamera.SetRot(Vector3(0, plus, 0));


	}


	// �s�b�N�̂����蔻��̍X�V
	m_CollisionNodeCamera.Update();
}



//-----------------------------------------------------------------------------
// �s��X�V
//-----------------------------------------------------------------------------
void DebugCamera::Calc()
{
	// �s��X�V
	m_ObjDebugCamera.Calc();

}





//-----------------------------------------------------------------------------
// �`��
//-----------------------------------------------------------------------------
void DebugCamera::Render()
{
	// �f�o�b�O�J�����`��
	//m_ObjDebugCamera.Render();

	// �����蔻��̕\�� --- �I��
	CollisionNode::SeetDebugVisible(true);
	m_CollisionNodeCamera.Draw();

}





//-----------------------------------------------------------------------------
// �㏈��
//-----------------------------------------------------------------------------
void DebugCamera::Finalize()
{

}




//-----------------------------------------------------------------------------
// �`��
//-----------------------------------------------------------------------------
const DirectX::SimpleMath::Vector3& DebugCamera::GetTrans()
{
	// �^���N�p�[�c�̍��W��Ԃ�
	return m_ObjDebugCamera.GetTrans();
}




//-----------------------------------------------------------------------------
// �`��
//-----------------------------------------------------------------------------
void DebugCamera::SetTrans(const DirectX::SimpleMath::Vector3& trans)
{
	// �^���N�p�[�c�̍��W��ݒ�
	m_ObjDebugCamera.SetTrans(trans);
}




//-----------------------------------------------------------------------------
// ��]���𓾂�
//-----------------------------------------------------------------------------
const DirectX::SimpleMath::Vector3& DebugCamera::GetRot()
{
	// �^���N�p�[�c�̉�]����Ԃ�
	return m_ObjDebugCamera.GetRot();
}





//-----------------------------------------------------------------------------
// ��]���𔽉f
//-----------------------------------------------------------------------------
void DebugCamera::SetRot(const DirectX::SimpleMath::Vector3& rot)
{
	// �^���N�p�[�c�̉�]����ݒ�
	m_ObjDebugCamera.SetRot(rot);
}





//-----------------------------------------------------------------------------
// ���[�J���̃��[���h�s��𓾂�
//-----------------------------------------------------------------------------
const DirectX::SimpleMath::Matrix& DebugCamera::GetLocalWorld()
{
	// �^���N�p�[�c�̃��[���h�s���Ԃ�
	return m_ObjDebugCamera.GetLocalWorld();
}




