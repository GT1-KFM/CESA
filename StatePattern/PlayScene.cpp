// ヘッダファイルの読み込み
#include "PlayScene.h"
#include "TitleScene.h"
#include <iostream>
#include "SceneManager.h"

// ネームスペース
using namespace std;



// シーンを初期化
Scene* PlayScene::pScene = nullptr;


//----------------------------------------------------------------------------
// 初期化
//----------------------------------------------------------------------------
void PlayScene::Initialize()
{




}


// ---------------------------------------------------------------------------
// 更新
//----------------------------------------------------------------------------
void PlayScene::Update()
{




}


// ---------------------------------------------------------------------------
// 描画
//----------------------------------------------------------------------------
void PlayScene::Render()
{

}





// ---------------------------------------------------------------------------
// インスタンスを取得
//----------------------------------------------------------------------------
Scene* PlayScene::GetInstance()
{
	if (pScene == nullptr)
		pScene = new PlayScene();
	return pScene;
}


// ---------------------------------------------------------------------------
// 実行する
//---------------------------------------------------------------------------- 
void PlayScene::Execute(ChangeScene* pChangeScene)
{
	Update();
	Render();

	cout << "Play" << endl;

	int a;

	cin >> a;

	if (a == 1)
	{
		pChangeScene->SceneChange(TitleScene::GetInstance());
	}
}


// ---------------------------------------------------------------------------
// オブジェクトを破棄
//----------------------------------------------------------------------------
void PlayScene::Dispose()
{
	if (pScene != nullptr)
		delete pScene;
}


