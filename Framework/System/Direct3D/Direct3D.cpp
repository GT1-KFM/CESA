//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Direct3D.cpp
//!
//! @brief  Direct3D�N���X�̃\�[�X�t�@�C��
//!
//! @date   2014/10/10
//!
//! @author ���� �W
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "Direct3D.h"




// ���C�u�����̒ǉ� ========================================================
#pragma comment(lib, "d3d11.lib")    // Direct3D11�p���C�u����


// �ÓI�����o�ϐ��̎���
Direct3D* Direct3D::m_pDirect3D = nullptr;