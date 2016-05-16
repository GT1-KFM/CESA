// 多重インクルード防止
#pragma once

// ヘッダの読み込み
#include "Scene.h"


// ---------------------------------------------------------------------------
// TitleSceneクラス
// ---------------------------------------------------------------------------
class TitleScene : public Scene
{

	// メンバ変数 --------------------------------------------------------
private:

	
	static Scene*							pScene;					// シーン格納用


	//	メンバ関数 --------------------------------------------------------
public:

	// 初期化
	void Initialize();

	// 更新
	void Update(ChangeScene* pChangeScene);

	// 描画
	void Render();

	// インスタンスの取得
	static Scene* GetInstance();

	// オブジェクトの破棄
	static void Dispose();

};
