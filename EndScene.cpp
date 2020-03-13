#include "DXUT.h"
#include "EndScene.h"

void EndScene::Init()
{
	cout << "INITENDSCENE" << endl;
	label = new Label();
	label->labeldistance = 30;
	label->Create_Label("SCORE", { 100,100 });
}

void EndScene::Update()
{

}

void EndScene::Exit()
{
	label->Delete_Label();
	delete label;
}
