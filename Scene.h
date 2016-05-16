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

	// 更新
	virtual void Update(ChangeScene* pChangeScene) = 0;

	// 描画
	virtual void Render() = 0;

};