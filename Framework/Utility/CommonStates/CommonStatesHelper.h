////////////////////////////////////////////////////////////////////////////
//! @file   CommonStatesHelper.h
//!
//! @brief  CommonStates�̃w���p�[�N���X�̃w�b�_
//!
//! @date   2016/5/24
//!
//! @author �ߓ��@�D�a
////////////////////////////////////////////////////////////////////////////



// ���d�C���N���[�h�̖h�~
#pragma once


// �w�b�_�t�@�C���̓ǂݍ���
#include<CommonStates.h>
#include "Framework\System\Direct3D\Direct3D.h"


// ---------------------------------------------------------------------------
// CommonStatesHelper�N���X
// ---------------------------------------------------------------------------
class CommonStatesHelper
{

	// �����o�ϐ� ------------------------------------------------------------
private:

	std::unique_ptr<DirectX::CommonStates>       m_pCommonStates;	// �R�����X�e�[�g


																	// �ÓI�����o�ϐ� --------------------------------------------------------
private:

	static CommonStatesHelper* m_pCommonStatesHelper;		// CommonStatesHelper�̃A�h���X	



															// �ÓI�����o�֐� ---------------------------------------------------------
public:


	// ------------------------------------------------------------------------
	//! @brief      m_pCommonStatesHelper�̃A�h���X���擾����
	//!
	//! @return     m_pCommonStatesHelper
	// ------------------------------------------------------------------------
	static CommonStatesHelper* GetInstance()
	{
		// �w���p�[����̏ꍇ����
		if (m_pCommonStatesHelper == nullptr)
			CommonStatesHelper::Create();

		return m_pCommonStatesHelper;
	}



private:

	// -------------------------------------------------------------------------
	//! @brief      m_pCommonStatesHelper�𐶐�����
	// -------------------------------------------------------------------------
	static void Create()
	{
		// �w���p�[�𐶐�
		m_pCommonStatesHelper = new CommonStatesHelper();

		// �R�����X�e�[�g�𐶐�
		m_pCommonStatesHelper->m_pCommonStates = std::make_unique<DirectX::CommonStates>(Direct3D::GetInstance()->GetDevice());
	}



public:


	// -------------------------------------------------------------------------
	//! @brief      �I�u�W�F�N�g�̔j��
	// -------------------------------------------------------------------------
	static void Dispose()
	{
		// ��łȂ��ꍇ�j������
		if (m_pCommonStatesHelper != nullptr)
			delete m_pCommonStatesHelper;
	}




	// �����o�֐� --------------------------------------------------------------
public:

	// -------------------------------------------------------------------------
	//! @brief      �R�����X�e�[�g�𓾂�
	//!
	//! @return     m_pCommonStates
	// -------------------------------------------------------------------------
	DirectX::CommonStates* GetCommonStates() const
	{
		return m_pCommonStates.get();
	}

};