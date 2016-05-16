// �w�b�_�t�@�C���̓ǂݍ���
#include "TitleScene.h"
#include <iostream>
#include "SceneManager.h"
#include "PlayScene.h"
// �l�[���X�y�[�X
using namespace std;
//using namespace DirectX;
//using namespace SimpleMath;
//using namespace Framework;

//class SceneManager;

// �V�[����������
Scene* TitleScene::pScene = nullptr;




// ---------------------------------------------------------------------------
// ������
//----------------------------------------------------------------------------
void TitleScene::Initialize()
{

	// �f�o�b�O�J��������
	//m_DebugCamera = make_unique<DebugCamera>();
	//m_DebugCamera->Initialize();

	//m_DebugCamera->SetInputManager(m_InputManager);



}


// ---------------------------------------------------------------------------
// �X�V
//----------------------------------------------------------------------------
void TitleScene::Update()
{

	//m_DebugCamera->Update();

	//TargetCamera(m_DebugCamera->GetTrans(), m_DebugCamera->GetRot());


	
}


// ---------------------------------------------------------------------------
// �`��
//----------------------------------------------------------------------------
void TitleScene::Render()
{
	
}




// ---------------------------------------------------------------------------
// �C���X�^���X���擾
//----------------------------------------------------------------------------
Scene* TitleScene::GetInstance()
{
	if (pScene == nullptr)
		pScene = new TitleScene();
	return pScene;
}


// ---------------------------------------------------------------------------
// ���s����
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
// �I�u�W�F�N�g��j��
//----------------------------------------------------------------------------
void TitleScene::Dispose()
{
	if (pScene != nullptr)
		delete pScene;
}