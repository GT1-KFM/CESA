//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Direct3D.cpp
//!
//! @brief  Direct3Dクラスのソースファイル
//!
//! @date   2014/10/10
//!
//! @author 高木 晋
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// ヘッダファイルの読み込み ================================================
#include "Direct3D.h"




// ライブラリの追加 ========================================================
#pragma comment(lib, "d3d11.lib")    // Direct3D11用ライブラリ



Direct3D* Direct3D::m_pDirect3D = nullptr;