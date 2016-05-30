
////////////////////////////////////////////////////////////////////////////
//! @file   Camera.h
//!
//! @brief  カメラのソースファイル
//!
//! @date   2016/05/27
//!
//! @author 近藤　優和
////////////////////////////////////////////////////////////////////////////


// ヘッダファイルの読み込み -----------------------------------------------
#include "Camera.h"
#include "..\System\Window\Window.h"



// 名前空間の使用宣言 -----------------------------------------------------
using namespace DirectX;
using namespace DirectX::SimpleMath;


//-------------------------------------------------------------------------
//! @ brief		コンストラクタ
//-------------------------------------------------------------------------
Camera::Camera()
{


}



//-------------------------------------------------------------------------
//! @brief		デストラクタ
//-------------------------------------------------------------------------
Camera::~Camera()
{

}




//-------------------------------------------------------------------------
//! @brief		初期化
//-------------------------------------------------------------------------
void Camera::Initialize()
{
	auto window = Window::GetInstance();

	// アスペクト比
	m_Aspect = ((float)window->GetScreenWidth() / (float)window->GetScreenHeight());
	// ファークリップ
	m_FarClip = 1000.0f;
	// カメラ座標
	m_z = -20.0f;
	m_x = 0.0f;
	// 	縦視野角
	m_FovY = XMConvertToRadians(60.0f);
	// ビュー行列
	m_Viewmat = Matrix::Identity;
	// カメラ座標
	m_Eyepos = Vector3(0.0f, 0.0f, 0.0f);
	// ターゲット座標
	m_Refpos = Vector3(0.0f, 7.0f, 0.0f);
	// 上方向ベクトル
	m_Upvec = Vector3(0.0f, 1.0f, 0.0f);
	// プロジェクション行列
	m_Projmat = Matrix::Identity;
}





//-------------------------------------------------------------------------
//! @brief		更新
//-------------------------------------------------------------------------
void Camera::Update()
{
	//ビュー行列を計算
	m_Viewmat = Matrix::CreateLookAt(m_Eyepos, m_Refpos, m_Upvec);

	//プロジェクション行列の計算
	m_Projmat = Matrix::CreatePerspectiveFieldOfView(m_FovY, m_Aspect,m_NearClip, m_FarClip);

}




void Camera::TargetCamera(Vec3 trans, Vec3 rot)
{
	
	Vec3 eyepos, refpos;
	//ターゲットの座標は、自機の座標に追従
	refpos = trans + Vec3(0, 1.0f, 0);
	//ターゲット座標からカメラ座標への差分
	Vec3 cameraV(0.0f, 0.0f, -3.0f);
	//カメラの視点方向の逆方向に回転
	SimpleMath::Matrix camera_rotmat = Matrix::CreateRotationY(rot.y);
	cameraV = Vec3::TransformNormal(cameraV, camera_rotmat);

	//カメラ座標を計算
	eyepos = refpos + cameraV;

	SimpleMath::Vector3 eye = m_Eyepos + (eyepos - m_Eyepos)*0.03f;
	SimpleMath::Vector3 ref = m_Refpos + (refpos - m_Refpos)*0.03f;

	//カメラに情報をセット
	this->SetEyepos(eye);
	this->SetRefpos(ref);
}