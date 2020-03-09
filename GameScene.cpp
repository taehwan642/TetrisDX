#include "DXUT.h"
#include "GameScene.h"

bool GameScene::check()
{
	for (int i = 0; i < 4; i++)
	{
		if (a[i].x < 0 || a[i].x >= Stage_Width || a[i].y >= Stage_Height)
		{
			cout << a[i].x << " " << a[i].y << endl;
			return false;
		}
		else if (field[(int)a[i].y][(int)a[i].x] == 1)
		{
			for (int i = 0; i < Stage_Height; i++)
			{
				for (int j = 0; j < Stage_Width; j++)
				{
					cout << field[i][j] << " ";
				}
				cout << endl << endl;
			}
			return false;
		}
	}
	return true;
}

void GameScene::Init()
{
	cout << "INIT" << endl;
	Camera::GetIns()->CameraInit();
	StageMNG::GetIns()->CreateStage();
	Camera::GetIns()->SetPos({ 500,300 });
	Camera::GetIns()->SetSize(1.3);
	time = 30000.3f;
	for (int i = 0; i < 4; i++)
	{
		a[i] = { 0,0 };
		b[i] = { 0,0 };
	}
	//Sprite* O[4];
	//Vec2 a[4];
	//int n = rand() % 8;
	//n = 3;
	//for (int i = 0; i < 4; i++)
	//{
	//	O[i] = new Sprite();
	//	O[i]->SetTexture(L"poly.png");
	//	a[i].x = tetrominosss[n][i] % 2;
	//	a[i].y = tetrominosss[n][i] / 2;
	//	cout << a[i].x << " " << a[i].y << endl;
	//	O[i]->_position = { a[i].x * 50 , a[i].y * 50 };
	//}   
	//// tetromino 클래스 제작 X 그냥 하나만 만들고, poly4개 만들어주고 그걸 일일이 다 어디 벡터에다가 박아줌.
	//field[0][5] = 1;
	//field[0][4] = 1;
	//field[1][5] = 1;
	//field[1][4] = 1;
	colornum = 1;
}

void GameScene::Update()
{
	Camera::GetIns()->Update();
	time += GLOBAL::deltatime;
	if (time > 0.3f)
	{
		cout << "tick" << endl;
		for (int i = 0; i < Stage_Height; i++)
		{
			for (int j = 0; j < Stage_Width; j++)
			{
				StageMNG::GetIns()->stagegrids[i][j]->SetTexture(L"Block.png"); // 초기화
			}
		}
		// 블록 조종
		for (int i = 0; i < 4; i++) { b[i] = a[i]; a[i].y++; }
		if (!check())
		{
			for (int i = 0; i < 4; i++) field[(int)b[i].y][(int)b[i].x] = colornum; // 조종하는 블록 맵에 설치 (놓아졌을때)
			colornum = 1;
			int n = rand() % 6;
			for (int i = 0; i < 4; i++)
			{
				a[i].x = tetrominosss[n][i] % 2;
				a[i].y = tetrominosss[n][i] / 2;
				//cout << a[i].x << " " << a[i].y << endl;

			}
		}
		
		time = 0;
	}
	for (int i = 0; i < Stage_Height; i++)
	{
		for (int j = 0; j < Stage_Width; j++)
		{
			if (field[i][j] == 0)
				continue;
			StageMNG::GetIns()->stagegrids[i][j]->SetTexture(L"poly.png");
			StageMNG::GetIns()->stagegrids[i][j]->_color = { 255,40,40,40 };
		}
	}
	for (int i = 0; i < 4; i++)
	{
		cout << a[i].x << " " << a[i].y << endl;

		StageMNG::GetIns()->stagegrids[a[i].y][a[i].x]->SetTexture(L"poly.png");
	}
}

void GameScene::Exit()
{
	cout << "EXIT" << endl;
	StageMNG::GetIns()->DeleteStage();
}
