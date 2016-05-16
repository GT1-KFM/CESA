// 多重インクルード防止
#pragma once

class Scene;


// ヘッダの読み込み



class ChangeScene
{

	// メンバ関数 ---------------------------------------------------------
public:

	// 純粋仮想関数
	virtual void SceneChange(Scene* currentScene) = 0;
};
