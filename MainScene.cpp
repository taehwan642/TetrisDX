#include "DXUT.h"
#include "MainScene.h"

void MainScene::Init()
{
	StageMNG::GetIns()->DeleteStage();
	StageMNG::GetIns()->DeleteOtherStage();
}

void MainScene::Update()
{
	if (DXUTWasKeyPressed('P'))
	{
		Director::GetIns()->SceneSet(new GameScene);
	}
}

void MainScene::Exit()
{

}
