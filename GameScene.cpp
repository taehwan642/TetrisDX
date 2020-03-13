#include "DXUT.h"
#include "GameScene.h"
// 해야할거 
// 4. 메인 씬 만들기
// 5. 소리 띄우기 


void GameScene::Init()
{
	cout << "INIT" << endl;
	Camera::GetIns()->CameraInit();
	StageMNG::GetIns()->CreateStage();
	//StageMNG::GetIns()->CreateOtherStage();
	Camera::GetIns()->SetPos({ 500,300 });
	Camera::GetIns()->SetSize(1.3);
	time = 0.3f;
	delay = 0.3f;
	label = new Label();
	scorelabel = new Label();
	nextlabel = new Label();
	label->_scale = { 2,2 };
	label->labeldistance = 50;
	nextlabel->labeldistance = 30;
	nextlabel->Create_Label("NEXT", { 710,450 });
	scorelabel->labeldistance = 30;
	scorelabel->Create_Label("SCORE", { 600,150 });
	label->Create_Label(GLOBAL::score, { 600,200 });
	StageMNG::GetIns()->StartTetris();
}

void GameScene::Update()
{
	Camera::GetIns()->Update();
	if (!GLOBAL::isgameover)
	{

		StageMNG::GetIns()->ReTextureTetris();
		//StageMNG::GetIns()->ReTextureOtherTetris();
		if (DXUTWasKeyPressed('A'))
		{
			StageMNG::GetIns()->dx = -1;
			// dx = -1;
		}
		else if (DXUTWasKeyPressed('D'))
		{
			StageMNG::GetIns()->dx = 1;
			// dx = 1;
		}
		if (DXUTWasKeyPressed('W'))
		{
			StageMNG::GetIns()->rotate = true;
			// rotate = true;
		}
		if (DXUTIsKeyDown('S'))
		{
			delay = 0.1f;
		}
		if (DXUTWasKeyPressed('P'))
		{
			Director::GetIns()->SceneSet(new EndScene);
			// debug
		}
		StageMNG::GetIns()->TetrominoMovement();
		StageMNG::GetIns()->TetrominoRotate();
		time += GLOBAL::deltatime;
		if (time > delay)
		{
			StageMNG::GetIns()->UpdateTetris();
			StageMNG::GetIns()->CreateTetromino();

			label->Create_Label(GLOBAL::score, { 600,200 });
			delay = 0.3f;
			time = 0;
		}
		StageMNG::GetIns()->rotate = false;
		StageMNG::GetIns()->dx = 0;
		//cout << StageMNG::GetIns()->otherstagegrids.size() << endl;
		StageMNG::GetIns()->CheckTetrisLine();
		StageMNG::GetIns()->SetTetrisTexture();
		//StageMNG::GetIns()->SetOtherTetrisTexture();
	}
	else
	{
		Director::GetIns()->SceneSet(new EndScene);
	}
}

void GameScene::Exit()
{
	StageMNG::GetIns()->DeleteStage();
	//if (StageMNG::GetIns()->otherstagegrids.size() == 10)
		//StageMNG::GetIns()->DeleteOtherStage();
	//else
	//{
		//Renderer::GetIns()->_rendertargets.clear();
	//}
	label->Delete_Label();
	delete label;
	nextlabel->Delete_Label();
	delete nextlabel;
	scorelabel->Delete_Label();
	delete scorelabel;
	cout << "EXIT" << endl;
}
