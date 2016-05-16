// 多重インクルード防止
#pragma once



// ヘッダファイルの読み込み
#include "Scene.h"
#include <map>
#include <string>
#include "ChangeScene.h"



// クラス定義
class SceneManager	: public ChangeScene
{

	// メンバ変数 ---------------------------------------------------------
private:

	Scene*									pCurrentScene;			// 現在のシーン

	// メンバ関数 ---------------------------------------------------------
public:

	// コンストラクタ
	SceneManager();


	// デストラクタ
	~SceneManager();


	// シーンを変更する
	void SceneChange(Scene* currentScene);

	// 初期化
	void Initialize();

	// 更新

	void Update();

	// 描画
	void Render();

	// 後処理
	void Finalize();


};
