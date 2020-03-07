#include "DXUT.h"
#include "GameScene.h"

void GameScene::Init()
{
	cout << "INIT" << endl;
	Camera::GetIns()->CameraInit();
	TetrominoMNG::GetIns()->CreateTetromino();
}

void GameScene::Update()
{

}

void GameScene::Exit()
{
	cout << "EXIT" << endl;
}
