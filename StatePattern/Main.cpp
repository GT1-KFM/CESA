// �w�b�_�̓ǂݍ���
#include <iostream>
#include "SceneManager.h"
#include "TitleScene.h"


int main()
{
	SceneManager* sm = new SceneManager();

	sm->SceneChange(TitleScene::GetInstance());

	while (true)
	{
		sm->Update();
	}

	sm->Finalize();
	delete sm;

	return 0;
}