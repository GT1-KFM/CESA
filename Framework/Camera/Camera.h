////////////////////////////////////////////////////////////////////////////
//! @file   Camera.h
//!
//! @brief  カメラのヘッダファイル
//!
//! @date   2016/05/27
//!
//! @author 近藤　優和
////////////////////////////////////////////////////////////////////////////



// 多重インクルード防止 ---------------------------------------------------
#pragma once

// ヘッダファイルの読み込み -----------------------------------------------
#include <SimpleMath.h>



// ---------------------------------------------------------------------------
// Cameraクラス
// ---------------------------------------------------------------------------
class Camera
{
	// 型 -------------------------------------------------------------------
private:

	using Vec3 = DirectX::SimpleMath::Vector3;
	using Matrix = DirectX::SimpleMath::Matrix;

	// メンバ変数 ------------------------------------------------------------
private:

	Matrix	m_Viewmat;	// ビュー行列
	Vec3	m_Eyepos;	// カメラ座標
	Vec3	m_Refpos;	//ターゲット座標
	Vec3	m_Upvec;	//上方向ベクトル
	Matrix	m_Projmat;	//プロジェクション行列

	float	m_FovY;		// 縦方向視野角
	float	m_Aspect;	// アスペクト比
	float	m_NearClip;	// ニアクリップ
	float	m_FarClip;	// ファークリップ

	float	m_x;		// 座標X
	float	m_z;		// 座標Y
	float	m_zoom;		//ズーム



	// コンストラクタ --------------------------------------------------------
public:

	Camera();


	// デストラクタ ----------------------------------------------------------
public:

	~Camera();


	// メンバ関数 ------------------------------------------------------------
public:

	// 初期化
	void Initialize();

	//更新
	void Update();

	// ターゲットを設定
	void TargetCamera(Vec3 trans,Vec3 rot);

	// カメラ座標を設定
	void SetEyepos(const Vec3 pos){ m_Eyepos = pos; }

	// ターゼット座標を設定
	void SetRefpos(const Vec3 pos){ m_Refpos = pos; }

	// 上方向ベクトルを設定
	void SetUpvec(const Vec3 vec){ m_Upvec = vec; }

	// 縦方向視野角の設定
	void SetFovY(const float fovy){ m_FovY = fovy; }

	// カメラ座標を得る
	const Vec3& GetEyepos()const{ return m_Eyepos; }

	// ターゲット座標を得る
	const Vec3& GetRefpos()const{ return m_Refpos; }

	// 上方向ベクトルを得る
	const Vec3& GetUpvec()const{ return m_Upvec; }

	// ビュー行列を得る
	const Matrix& GetViewmat()const{ return m_Viewmat; }

	// プロジェクション行列を得る
	const Matrix& GetProjmat()const{ return m_Projmat; }
};