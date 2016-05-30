////////////////////////////////////////////////////////////////////////////
//! @file   CommonStatesHelper.h
//!
//! @brief  CommonStatesのヘルパークラスのヘッダ
//!
//! @date   2016/5/24
//!
//! @author 近藤　優和
////////////////////////////////////////////////////////////////////////////



// 多重インクルードの防止
#pragma once


// ヘッダファイルの読み込み
#include<CommonStates.h>
#include "Framework\System\Direct3D\Direct3D.h"


// ---------------------------------------------------------------------------
// CommonStatesHelperクラス
// ---------------------------------------------------------------------------
class CommonStatesHelper
{

	// メンバ変数 ------------------------------------------------------------
private:

	std::unique_ptr<DirectX::CommonStates>       m_pCommonStates;	// コモンステート


																	// 静的メンバ変数 --------------------------------------------------------
private:

	static CommonStatesHelper* m_pCommonStatesHelper;		// CommonStatesHelperのアドレス	



															// 静的メンバ関数 ---------------------------------------------------------
public:


	// ------------------------------------------------------------------------
	//! @brief      m_pCommonStatesHelperのアドレスを取得する
	//!
	//! @return     m_pCommonStatesHelper
	// ------------------------------------------------------------------------
	static CommonStatesHelper* GetInstance()
	{
		// ヘルパーが空の場合生成
		if (m_pCommonStatesHelper == nullptr)
			CommonStatesHelper::Create();

		return m_pCommonStatesHelper;
	}



private:

	// -------------------------------------------------------------------------
	//! @brief      m_pCommonStatesHelperを生成する
	// -------------------------------------------------------------------------
	static void Create()
	{
		// ヘルパーを生成
		m_pCommonStatesHelper = new CommonStatesHelper();

		// コモンステートを生成
		m_pCommonStatesHelper->m_pCommonStates = std::make_unique<DirectX::CommonStates>(Direct3D::GetInstance()->GetDevice());
	}



public:


	// -------------------------------------------------------------------------
	//! @brief      オブジェクトの破棄
	// -------------------------------------------------------------------------
	static void Dispose()
	{
		// 空でない場合破棄する
		if (m_pCommonStatesHelper != nullptr)
			delete m_pCommonStatesHelper;
	}




	// メンバ関数 --------------------------------------------------------------
public:

	// -------------------------------------------------------------------------
	//! @brief      コモンステートを得る
	//!
	//! @return     m_pCommonStates
	// -------------------------------------------------------------------------
	DirectX::CommonStates* GetCommonStates() const
	{
		return m_pCommonStates.get();
	}

};