#include "DXUT.h"
#include "EndScene.h"

void EndScene::Init()
{
	cout << "INITENDSCENE" << endl;
	label = new Label();
	label->labeldistance = 30;
	scorelabel = new Label();
	scorelabel->labeldistance = 30;
	label->Create_Label("SCORE", { 100,100 });
	scorelabel->Create_Label(GLOBAL::score, { 100,150 });
	rest = new Label();
	rest->labeldistance = 20;
	rest->Create_Label("Press R to Restart", { 300,500 });
}

void EndScene::Update()
{
	if (DXUTWasKeyPressed('R'))
		Director::GetIns()->SceneSet(new MainScene);
}

void EndScene::Exit()
{
	label->Delete_Label();
	scorelabel->Delete_Label();
	rest->Delete_Label();
	delete label;
	delete scorelabel;
	delete rest;
}
