////////////////////////////////////////////////////////////////////////////
//! @file   Camera.h
//!
//! @brief  �J�����̃w�b�_�t�@�C��
//!
//! @date   2016/05/27
//!
//! @author �ߓ��@�D�a
////////////////////////////////////////////////////////////////////////////



// ���d�C���N���[�h�h�~ ---------------------------------------------------
#pragma once

// �w�b�_�t�@�C���̓ǂݍ��� -----------------------------------------------
#include <SimpleMath.h>



// ---------------------------------------------------------------------------
// Camera�N���X
// ---------------------------------------------------------------------------
class Camera
{
	// �^ -------------------------------------------------------------------
private:

	using Vec3 = DirectX::SimpleMath::Vector3;
	using Matrix = DirectX::SimpleMath::Matrix;

	// �����o�ϐ� ------------------------------------------------------------
private:

	Matrix	m_Viewmat;	// �r���[�s��
	Vec3	m_Eyepos;	// �J�������W
	Vec3	m_Refpos;	//�^�[�Q�b�g���W
	Vec3	m_Upvec;	//������x�N�g��
	Matrix	m_Projmat;	//�v���W�F�N�V�����s��

	float	m_FovY;		// �c��������p
	float	m_Aspect;	// �A�X�y�N�g��
	float	m_NearClip;	// �j�A�N���b�v
	float	m_FarClip;	// �t�@�[�N���b�v

	float	m_x;		// ���WX
	float	m_z;		// ���WY
	float	m_zoom;		//�Y�[��



	// �R���X�g���N�^ --------------------------------------------------------
public:

	Camera();


	// �f�X�g���N�^ ----------------------------------------------------------
public:

	~Camera();


	// �����o�֐� ------------------------------------------------------------
public:

	// ������
	void Initialize();

	//�X�V
	void Update();

	// �^�[�Q�b�g��ݒ�
	void TargetCamera(Vec3 trans,Vec3 rot);

	// �J�������W��ݒ�
	void SetEyepos(const Vec3 pos){ m_Eyepos = pos; }

	// �^�[�[�b�g���W��ݒ�
	void SetRefpos(const Vec3 pos){ m_Refpos = pos; }

	// ������x�N�g����ݒ�
	void SetUpvec(const Vec3 vec){ m_Upvec = vec; }

	// �c��������p�̐ݒ�
	void SetFovY(const float fovy){ m_FovY = fovy; }

	// �J�������W�𓾂�
	const Vec3& GetEyepos()const{ return m_Eyepos; }

	// �^�[�Q�b�g���W�𓾂�
	const Vec3& GetRefpos()const{ return m_Refpos; }

	// ������x�N�g���𓾂�
	const Vec3& GetUpvec()const{ return m_Upvec; }

	// �r���[�s��𓾂�
	const Matrix& GetViewmat()const{ return m_Viewmat; }

	// �v���W�F�N�V�����s��𓾂�
	const Matrix& GetProjmat()const{ return m_Projmat; }
};