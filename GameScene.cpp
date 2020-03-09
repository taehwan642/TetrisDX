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
				cout << endl;
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
	int n = rand() % 7;
	for (int i = 0; i < 4; i++)
	{
		a[i].x = (tetrominosss[n][i] % 2) + 3;
		a[i].y = (tetrominosss[n][i] / 2);
		//cout << a[i].x << " " << a[i].y << endl;

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
	dx = 0;
	rotate = false;
	delay = 0.3f;
}

void GameScene::Update()
{
	Camera::GetIns()->Update();
	if (DXUTIsKeyDown('A'))
		dx = -1;
	else if (DXUTIsKeyDown('D'))
		dx = 1;
	 if (DXUTWasKeyPressed('W'))
		rotate = true;
	 if (DXUTIsKeyDown('S'))
		delay = 0.03f;
	time += GLOBAL::deltatime;
	if (time > delay)
	{
		for (int i = 0; i < 4; i++) { b[i] = a[i]; a[i].x += dx; }
		if (!check()) for (int i = 0; i < 4; i++) a[i] = b[i];


		if (rotate)
		{
			Vec2 p = a[1]; //center of rotation
			for (int i = 0; i < 4; i++)
			{
				int x = a[i].y - p.y;
				int y = a[i].x - p.x;
				a[i].x = p.x - x;
				a[i].y = p.y + y;
			}
			if (!check()) for (int i = 0; i < 4; i++) a[i] = b[i];
		}

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
				a[i].x = (tetrominosss[n][i] % 2) + 3;
				a[i].y = (tetrominosss[n][i] / 2);

				//cout << a[i].x << " " << a[i].y << endl;

			}
		}
		dx = 0;
		time = 0;
		delay = 0.3f;
		rotate = false;
	}
	int k = Stage_Height - 1;
	for (int i = Stage_Height - 1; i > 0; i--)
	{
		int count = 0;
		for (int j = 0; j < Stage_Width; j++)
		{
			if (field[i][j]) count++;
			field[k][j] = field[i][j];
		}
		if (count < Stage_Width) k--;
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
		if (a[i].y < 0)
		{
			exit(1);
			return;
		}
		StageMNG::GetIns()->stagegrids[a[i].y][a[i].x]->SetTexture(L"poly.png");
	}
}

void GameScene::Exit()
{
	cout << "EXIT" << endl;
	StageMNG::GetIns()->DeleteStage();
}
