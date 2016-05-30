// ヘッダファイルの読み込み
#include "DebugCamera.h"
#include "Game\Collision\Collision.h"
#include "..\Input\InputManager.h"

// ネームスペース
using namespace DirectX;
using namespace DirectX::SimpleMath;




// ---------------------------------------------------------------------------
// コンストラクタ
//----------------------------------------------------------------------------
DebugCamera::DebugCamera()
//	:Charactor()
{
}




// ---------------------------------------------------------------------------
// デストラクタ
//----------------------------------------------------------------------------
DebugCamera::~DebugCamera()
{
}




//-----------------------------------------------------------------------------
// 初期化
//-----------------------------------------------------------------------------
void DebugCamera::Initialize()
{
	// デバッグカメラ
	//m_ObjDebugCamera.LoadModelFile(L"Resources/cModels/ball.cmo");
	m_ObjDebugCamera.LoadModelFile(L"Resources/cModels/LockBase.cmo");

	
	// ピンのあたり判定の設定
	// 初期化
	m_CollisionNodeCamera.Initialize();
	// 親の設定
	m_CollisionNodeCamera.SetParentMatrix(&m_ObjDebugCamera.GetLocalWorld());
	// ローカル半径
	m_CollisionNodeCamera.SetLocalRadius(0.05f);
	// ローカルの高さ
	m_CollisionNodeCamera.SetLength(0.1f);
	// 親からの距離
	m_CollisionNodeCamera.SetTrans(Vector3(0.0f, 0.05f, 0.0f));

}



//-----------------------------------------------------------------------------
// 更新
//-----------------------------------------------------------------------------
void DebugCamera::Update()
{
	// １フレームでの旋回速度<ラジアン>
	const float ROT_SPEED = 0.05f;
	const float MOVE_SPEED = 0.05f;

	auto input = InputManager::GetInstance();

	//-------------------------------------------------------------------
	// 平行移動

	// 前進
	if (input->GetKeyboard()->IsKeyDown('W'))
	{
		SimpleMath::Vector3 trans = m_ObjDebugCamera.GetTrans();
		const SimpleMath::Vector3& rot = m_ObjDebugCamera.GetRot();

		//移動ベクトル(W座標前進)
		SimpleMath::Vector3 moveV(0, 0, 0.1f);
		SimpleMath::Matrix rotmat = SimpleMath::Matrix::CreateRotationY(rot.y);
		moveV = SimpleMath::Vector3::Transform(moveV, rotmat);
		//自機の座標を移動
		trans += moveV;

		// 反映させる
		m_ObjDebugCamera.SetTrans(trans);
	}
	// 後退
	if (input->GetKeyboard()->IsKeyDown('S'))
	{
		SimpleMath::Vector3 trans = m_ObjDebugCamera.GetTrans();
		const SimpleMath::Vector3& rot = m_ObjDebugCamera.GetRot();

		//移動ベクトル(W座標前進)
		SimpleMath::Vector3 moveV(0, 0, 0.1f);
		SimpleMath::Matrix rotmat = SimpleMath::Matrix::CreateRotationY(rot.y);
		moveV = SimpleMath::Vector3::Transform(moveV, rotmat);
		//自機の座標を移動
		trans -= moveV;

		// 反映させる
		m_ObjDebugCamera.SetTrans(trans);
	}

	// 右進
	if (input->GetKeyboard()->IsKeyDown('A'))
	{
		SimpleMath::Vector3 trans = m_ObjDebugCamera.GetTrans();
		const SimpleMath::Vector3& rot = m_ObjDebugCamera.GetRot();

		//移動ベクトル(W座標前進)
		SimpleMath::Vector3 moveV(-0.01f, 0.0f, 0.0f);
		SimpleMath::Matrix rotmat = SimpleMath::Matrix::CreateRotationY(rot.y);
		moveV = SimpleMath::Vector3::Transform(moveV, rotmat);
		//自機の座標を移動
		trans -= moveV;

		// 反映させる
		m_ObjDebugCamera.SetTrans(trans);
	}
	// 左進
	if (input->GetKeyboard()->IsKeyDown('D'))
	{
		SimpleMath::Vector3 trans = m_ObjDebugCamera.GetTrans();
		const SimpleMath::Vector3& rot = m_ObjDebugCamera.GetRot();

		//移動ベクトル(W座標前進)
		SimpleMath::Vector3 moveV(0.01f, 0.0f, 0.0f);
		SimpleMath::Matrix rotmat = SimpleMath::Matrix::CreateRotationY(rot.y);
		moveV = SimpleMath::Vector3::Transform(moveV, rotmat);
		//自機の座標を移動
		trans -= moveV;

		// 反映させる
		m_ObjDebugCamera.SetTrans(trans);
	}


	//--------------------------------------------------------------------------
	// 回転
	// 左回転
	if (input->GetKeyboard()->IsKeyDown('Q'))
	{
		m_ObjDebugCamera.SetQuternion(false);
		//回転ベクトル
		Vector3 rot = m_ObjDebugCamera.GetRot();
		float plus = rot.y += ROT_SPEED;

		m_ObjDebugCamera.SetRot(Vector3(0, plus, 0));


	}
	// 
	if (input->GetKeyboard()->IsKeyDown('E'))
	{
		m_ObjDebugCamera.SetQuternion(false);
		//回転ベクトル
		Vector3 rot = m_ObjDebugCamera.GetRot();
		float plus = rot.y -= ROT_SPEED;

		m_ObjDebugCamera.SetRot(Vector3(0, plus, 0));


	}


	// ピックのあたり判定の更新
	m_CollisionNodeCamera.Update();
}



//-----------------------------------------------------------------------------
// 行列更新
//-----------------------------------------------------------------------------
void DebugCamera::Calc()
{
	// 行列更新
	m_ObjDebugCamera.Calc();

}





//-----------------------------------------------------------------------------
// 描画
//-----------------------------------------------------------------------------
void DebugCamera::Render()
{
	// デバッグカメラ描画
	//m_ObjDebugCamera.Render();

	// あたり判定の表示 --- オン
	CollisionNode::SeetDebugVisible(true);
	m_CollisionNodeCamera.Draw();

}





//-----------------------------------------------------------------------------
// 後処理
//-----------------------------------------------------------------------------
void DebugCamera::Finalize()
{

}




//-----------------------------------------------------------------------------
// 描画
//-----------------------------------------------------------------------------
const DirectX::SimpleMath::Vector3& DebugCamera::GetTrans()
{
	// タンクパーツの座標を返す
	return m_ObjDebugCamera.GetTrans();
}




//-----------------------------------------------------------------------------
// 描画
//-----------------------------------------------------------------------------
void DebugCamera::SetTrans(const DirectX::SimpleMath::Vector3& trans)
{
	// タンクパーツの座標を設定
	m_ObjDebugCamera.SetTrans(trans);
}




//-----------------------------------------------------------------------------
// 回転率を得る
//-----------------------------------------------------------------------------
const DirectX::SimpleMath::Vector3& DebugCamera::GetRot()
{
	// タンクパーツの回転率を返す
	return m_ObjDebugCamera.GetRot();
}





//-----------------------------------------------------------------------------
// 回転率を反映
//-----------------------------------------------------------------------------
void DebugCamera::SetRot(const DirectX::SimpleMath::Vector3& rot)
{
	// タンクパーツの回転率を設定
	m_ObjDebugCamera.SetRot(rot);
}





//-----------------------------------------------------------------------------
// ローカルのワールド行列を得る
//-----------------------------------------------------------------------------
const DirectX::SimpleMath::Matrix& DebugCamera::GetLocalWorld()
{
	// タンクパーツのワールド行列を返す
	return m_ObjDebugCamera.GetLocalWorld();
}




