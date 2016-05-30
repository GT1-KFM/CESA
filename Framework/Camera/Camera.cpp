
////////////////////////////////////////////////////////////////////////////
//! @file   Camera.h
//!
//! @brief  �J�����̃\�[�X�t�@�C��
//!
//! @date   2016/05/27
//!
//! @author �ߓ��@�D�a
////////////////////////////////////////////////////////////////////////////


// �w�b�_�t�@�C���̓ǂݍ��� -----------------------------------------------
#include "Camera.h"
#include "..\System\Window\Window.h"



// ���O��Ԃ̎g�p�錾 -----------------------------------------------------
using namespace DirectX;
using namespace DirectX::SimpleMath;


//-------------------------------------------------------------------------
//! @ brief		�R���X�g���N�^
//-------------------------------------------------------------------------
Camera::Camera()
{


}



//-------------------------------------------------------------------------
//! @brief		�f�X�g���N�^
//-------------------------------------------------------------------------
Camera::~Camera()
{

}




//-------------------------------------------------------------------------
//! @brief		������
//-------------------------------------------------------------------------
void Camera::Initialize()
{
	auto window = Window::GetInstance();

	// �A�X�y�N�g��
	m_Aspect = ((float)window->GetScreenWidth() / (float)window->GetScreenHeight());
	// �t�@�[�N���b�v
	m_FarClip = 1000.0f;
	// �J�������W
	m_z = -20.0f;
	m_x = 0.0f;
	// 	�c����p
	m_FovY = XMConvertToRadians(60.0f);
	// �r���[�s��
	m_Viewmat = Matrix::Identity;
	// �J�������W
	m_Eyepos = Vector3(0.0f, 0.0f, 0.0f);
	// �^�[�Q�b�g���W
	m_Refpos = Vector3(0.0f, 7.0f, 0.0f);
	// ������x�N�g��
	m_Upvec = Vector3(0.0f, 1.0f, 0.0f);
	// �v���W�F�N�V�����s��
	m_Projmat = Matrix::Identity;
}





//-------------------------------------------------------------------------
//! @brief		�X�V
//-------------------------------------------------------------------------
void Camera::Update()
{
	//�r���[�s����v�Z
	m_Viewmat = Matrix::CreateLookAt(m_Eyepos, m_Refpos, m_Upvec);

	//�v���W�F�N�V�����s��̌v�Z
	m_Projmat = Matrix::CreatePerspectiveFieldOfView(m_FovY, m_Aspect,m_NearClip, m_FarClip);

}




void Camera::TargetCamera(Vec3 trans, Vec3 rot)
{
	
	Vec3 eyepos, refpos;
	//�^�[�Q�b�g�̍��W�́A���@�̍��W�ɒǏ]
	refpos = trans + Vec3(0, 1.0f, 0);
	//�^�[�Q�b�g���W����J�������W�ւ̍���
	Vec3 cameraV(0.0f, 0.0f, -3.0f);
	//�J�����̎��_�����̋t�����ɉ�]
	SimpleMath::Matrix camera_rotmat = Matrix::CreateRotationY(rot.y);
	cameraV = Vec3::TransformNormal(cameraV, camera_rotmat);

	//�J�������W���v�Z
	eyepos = refpos + cameraV;

	SimpleMath::Vector3 eye = m_Eyepos + (eyepos - m_Eyepos)*0.03f;
	SimpleMath::Vector3 ref = m_Refpos + (refpos - m_Refpos)*0.03f;

	//�J�����ɏ����Z�b�g
	this->SetEyepos(eye);
	this->SetRefpos(ref);
}