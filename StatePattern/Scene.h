// 多重インクルード防止
#pragma once

// 前方宣言
class ChangeScene;

// クラス宣言
class Scene
{


	// メンバ関数 --------------------------------------------------------
public:


	// 仮想デストラクタ
	virtual ~Scene() {}

	// 純粋仮想関数
	virtual void Execute(ChangeScene* pChangeScene) = 0;

};