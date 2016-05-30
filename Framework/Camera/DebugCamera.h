
// 多重インクルード防止 
#pragma once 

// ヘッダファイルの読み込み
#include <SimpleMath.h>
#include"Framework\Input\InputManager.h"
#include "..\Graphics\Obj3D.h"
#include "Game\Collision\CollisionNode.h"

// ---------------------------------------------------------------------------
// DebugCameraクラス
// ---------------------------------------------------------------------------
class DebugCamera //: public Charactor
{
	
	//	メンバ関数 --------------------------------------------------------
public:

	// コンストラクタ
	DebugCamera();
	// デストラクタ
	~DebugCamera();

	// 初期化
	void Initialize();

	// 更新
	void Update();

	// 行列の計算
	void Calc();

	// 描画
	void Render();

	// 後処理
	void Finalize();

	// セッター -----------------------------------------------------------

	// 座標を取得
	const DirectX::SimpleMath::Vector3& GetTrans();
	// 座標を設定
	void SetTrans(const DirectX::SimpleMath::Vector3& trans);
	// 回転率を取得
	const DirectX::SimpleMath::Vector3& GetRot();
	// 回転率を設定
	void SetRot(const DirectX::SimpleMath::Vector3& rot);
	// ワールド行列を取得
	const DirectX::SimpleMath::Matrix& GetLocalWorld();
	// 入力マネージャを設定


protected:
	// メンバ変数

	Obj3D m_ObjDebugCamera;					// 錠前のオブジェクト



	//int 

	SphereNode m_CollisionNodeCamera;				// ピンあたり判定


};



