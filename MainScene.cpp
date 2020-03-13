#include "DXUT.h"
#include "MainScene.h"

void MainScene::Init()
{
	start = new Label();
	exit = new Label();
	main = new Label();
	start->labeldistance = 20;
	exit->labeldistance = 20;
	main->labeldistance = 15;
	main->_scale = { 2,2 };
	main->Create_Label("TETRIS DX", { 300, 200 });
	start->Create_Label("Press SPACEBAR to Start", { 300, 500 });
	exit->Create_Label("Press ESC to Exit", { 300, 550 });
}

void MainScene::Update()
{
	if (DXUTWasKeyPressed(VK_SPACE))
	{
		Director::GetIns()->SceneSet(new GameScene);
	}
}

void MainScene::Exit()
{
	start->Delete_Label();
	exit->Delete_Label();
	main->Delete_Label();
	delete start;
	delete main;
	delete exit;
}
