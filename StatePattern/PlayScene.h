// 多重インクルード防止
#pragma once

// ヘッダの読み込み
#include "Scene.h"


#define TO_STRING(VariableName) # VariableName



// ---------------------------------------------------------------------------
// PlaySceneクラス
// ---------------------------------------------------------------------------
class PlayScene : public Scene
{

	// メンバ変数 ------------------------------------------------------------
private:


	static Scene*							pScene;					// シーン格納用


	//	メンバ関数 ----------------------------------------------------------
public:

	// 初期化
	void Initialize();

	// 更新
	void Update();

	// 描画
	void Render();

private:


public:
	// インスタンスの取得
	static Scene* GetInstance();

	// 実行
	void Execute(ChangeScene* pChangeScene);


	// オブジェクトの破棄
	static void Dispose();

};

