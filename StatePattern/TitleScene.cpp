// ヘッダファイルの読み込み
#include "TitleScene.h"
#include <iostream>
#include "SceneManager.h"
#include "PlayScene.h"
// ネームスペース
using namespace std;
//using namespace DirectX;
//using namespace SimpleMath;
//using namespace Framework;

//class SceneManager;

// シーンを初期化
Scene* TitleScene::pScene = nullptr;




// ---------------------------------------------------------------------------
// 初期化
//----------------------------------------------------------------------------
void TitleScene::Initialize()
{

	// デバッグカメラ生成
	//m_DebugCamera = make_unique<DebugCamera>();
	//m_DebugCamera->Initialize();

	//m_DebugCamera->SetInputManager(m_InputManager);



}


// ---------------------------------------------------------------------------
// 更新
//----------------------------------------------------------------------------
void TitleScene::Update()
{

	//m_DebugCamera->Update();

	//TargetCamera(m_DebugCamera->GetTrans(), m_DebugCamera->GetRot());


	
}


// ---------------------------------------------------------------------------
// 描画
//----------------------------------------------------------------------------
void TitleScene::Render()
{
	
}




// ---------------------------------------------------------------------------
// インスタンスを取得
//----------------------------------------------------------------------------
Scene* TitleScene::GetInstance()
{
	if (pScene == nullptr)
		pScene = new TitleScene();
	return pScene;
}


// ---------------------------------------------------------------------------
// 実行する
//---------------------------------------------------------------------------- 
void TitleScene::Execute(ChangeScene* pChangeScene)
{


	Update();
	Render();

	cout << "Title" << endl;

	int a;

	cin >> a;

	if (a == 2)
	{
		pChangeScene->SceneChange(PlayScene::GetInstance());
	}
}


// ---------------------------------------------------------------------------
// オブジェクトを破棄
//----------------------------------------------------------------------------
void TitleScene::Dispose()
{
	if (pScene != nullptr)
		delete pScene;
}