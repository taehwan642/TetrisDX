#include "DXUT.h"
#include "GameScene.h"
// 해야할거 
// 4. 메인 씬 만들기
// 5. 소리 띄우기 
bool GameScene::check()
{
	for (int i = 0; i < 4; i++)
	{
		if (scenechange)
			continue;
		if (a[i].x < 0 || a[i].x >= Stage_Width || a[i].y >= Stage_Height)
		{
			return false;
		}
		else if (field[(int)a[i].y][(int)a[i].x] && a[i].y >= 0)
		{
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
	StageMNG::GetIns()->CreateOtherStage();
	Camera::GetIns()->SetPos({ 500,300 });
	Camera::GetIns()->SetSize(1.3);
	time = 0.3f;
	for (int i = 0; i < 4; i++)
	{
		a[i] = { 0,0 };
		b[i] = { 0,0 };
		c[i] = { 0,0 };
	}
	nextnum = rand() % 7;
	int n = nextnum;
	nextnum = rand() % 7;
	for (int i = 0; i < 4; i++)
	{
		c[i].x = (tetrominosss[nextnum][i] % 2);
		c[i].y = (tetrominosss[nextnum][i] / 2);

		a[i].x = (tetrominosss[n][i] % 2) + 3;
		a[i].y = (tetrominosss[n][i] / 2) - 3;
		//cout << a[i].x << " " << a[i].y << endl;
	}

	nextcolornum = nextnum + 1;
	colornum = n + 1;
	dx = 0;
	rotate = false;
	delay = 0.3f;
	label = new Label();
	scorelabel = new Label();
	nextlabel = new Label();
	score = 0;
	label->_scale = { 2,2 };
	label->labeldistance = 50;
	nextlabel->labeldistance = 30;
	nextlabel->Create_Label("NEXT", { 710,450 });
	scorelabel->labeldistance = 30;
	scorelabel->Create_Label("SCORE", { 600,150 });
	label->Create_Label(score, { 600,200 });
	scenechange = false;
}

void GameScene::Update()
{
	for (int i = 0; i < Stage_Height; i++)
	{
		for (int j = 0; j < Stage_Width; j++)
		{
			if (!scenechange)
			{
				StageMNG::GetIns()->stagegrids[i][j]->SetTexture(L"Block.png"); // 초기화
				StageMNG::GetIns()->stagegrids[i][j]->_color = { 255,255,255,255 };
			}
		}
	}
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if (!scenechange)
			{
				StageMNG::GetIns()->otherstagegrids[i][j]->SetTexture(L"Block.png");
				StageMNG::GetIns()->otherstagegrids[i][j]->_color = { 255,255,255,255 };
			}
		}
	}
	Camera::GetIns()->Update();
	if (DXUTWasKeyPressed('A'))
		dx = -1;
	else if (DXUTWasKeyPressed('D'))
		dx = 1;
	if (DXUTWasKeyPressed('W'))
		rotate = true;
	if (DXUTIsKeyDown('S'))
		delay = 0.1f;
	if (DXUTWasKeyPressed('P'))
	{
		scenechange = !scenechange;
	}
	for (int i = 0; i < 4; i++) { b[i] = a[i]; a[i].x += dx; }
	if (!check() && !scenechange)
		for (int i = 0; i < 4; i++)
		{
			if (a[i].y < 0) // 게임 진거임
			{
				scenechange = true;
				cout << "end" << endl;
				return;
			}
			a[i] = b[i];
		}

	//cout << "1" << endl;

	if (rotate && !scenechange)
	{
		Vec2 p = a[1]; //center of rotation
		for (int i = 0; i < 4; i++)
		{
			int x = a[i].y - p.y;
			int y = a[i].x - p.x;
			a[i].x = p.x - x;
			a[i].y = p.y + y;
		} // 반대로 회전행렬 입히기 Q, E 사용
		if (!check()) for (int i = 0; i < 4; i++) a[i] = b[i];
	}
	time += GLOBAL::deltatime;
	if (time > delay)
	{

		for (int i = 0; i < 4; i++) { b[i] = a[i]; a[i].y++; }
		if (!check())
		{
			if (!scenechange)
			{
				for (int i = 0; i < 4; i++) field[(int)b[i].y][(int)b[i].x] = colornum; // 조종하는 블록 맵에 설치 (놓아졌을때)
				score += 10;
				label->Create_Label(score, { 600,200 });

				int n = nextnum;
				currnum = nextnum;
				while (currnum == nextnum)
				{
					nextnum = rand() % 7;
				}
				nextcolornum = nextnum + 1;
				colornum = n + 1;

				for (int i = 0; i < 4; i++)
				{
					c[i].x = (tetrominosss[nextnum][i] % 2);
					c[i].y = (tetrominosss[nextnum][i] / 2);

					a[i].x = (tetrominosss[n][i] % 2) + 3;
					a[i].y = (tetrominosss[n][i] / 2) - 3;
				}
			}
			
		}
		delay = 0.3f;
		time = 0;
	}
	dx = 0;
	rotate = false;

	//cout << "2" << endl;

	int k = Stage_Height - 1;
	for (int i = Stage_Height - 1; i > 0; i--)
	{
		if (scenechange)
			continue;
		int count = 0;
		for (int j = 0; j < Stage_Width; j++)
		{
			if (field[i][j]) count++;
			field[k][j] = field[i][j];
		}
		if (count < Stage_Width) k--;
		else
		{
			score += 100;
			label->Create_Label(score, { 600,200 });
		}
	}


	for (int i = 0; i < Stage_Height; i++)
	{
		for (int j = 0; j < Stage_Width; j++)
		{
			if (field[i][j] == 0 || scenechange)
				continue;

			StageMNG::GetIns()->stagegrids[i][j]->SetTexture(L"poly.png");
			switch (field[i][j])
			{
			case 1:
				StageMNG::GetIns()->stagegrids[i][j]->_color = { 0, 200, 200, 255 };
				break;
			case 2:
				StageMNG::GetIns()->stagegrids[i][j]->_color = { 255, 0, 0, 255 };
				break;
			case 3:
				StageMNG::GetIns()->stagegrids[i][j]->_color = { 0, 255, 0, 255 };
				break;
			case 4:
				StageMNG::GetIns()->stagegrids[i][j]->_color = { 255,0,204,255 };
				break;
			case 5:
				StageMNG::GetIns()->stagegrids[i][j]->_color = { 1, 0.5f, 0, 255 };
				break;
			case 6:
				StageMNG::GetIns()->stagegrids[i][j]->_color = { 0, 0, 255, 255 };
				break;
			case 7:
				StageMNG::GetIns()->stagegrids[i][j]->_color = { 255, 255, 0, 255 };
				break;
			default:
				break;
			}
		}
	}
	//cout << "3" << endl;

	for (int i = 0; i < 4; i++)
	{
		StageMNG::GetIns()->otherstagegrids[c[i].y + 1][c[i].x + 2]->SetTexture(L"poly.png");
		switch (nextcolornum)
		{
		case 1:
			StageMNG::GetIns()->otherstagegrids[c[i].y + 1][c[i].x + 2]->_color = { 0, 200, 200, 255 };
			break;
		case 2:
			StageMNG::GetIns()->otherstagegrids[c[i].y + 1][c[i].x + 2]->_color = { 255, 0, 0, 255 };
			break;
		case 3:
			StageMNG::GetIns()->otherstagegrids[c[i].y + 1][c[i].x + 2]->_color = { 0, 255, 0, 255 };
			break;
		case 4:
			StageMNG::GetIns()->otherstagegrids[c[i].y + 1][c[i].x + 2]->_color = { 255,0,204,255 };
			break;
		case 5:
			StageMNG::GetIns()->otherstagegrids[c[i].y + 1][c[i].x + 2]->_color = { 1, 0.5f, 0, 255 };
			break;
		case 6:
			StageMNG::GetIns()->otherstagegrids[c[i].y + 1][c[i].x + 2]->_color = { 0, 0, 255, 255 };
			break;
		case 7:
			StageMNG::GetIns()->otherstagegrids[c[i].y + 1][c[i].x + 2]->_color = { 255, 255, 0, 255 };
			break;
		default:
			break;
		}
		if (a[i].y < 0 || scenechange)
		{
			continue;
		}
	
		StageMNG::GetIns()->stagegrids[a[i].y][a[i].x]->SetTexture(L"poly.png");
		switch (colornum)
		{
		case 1:
			StageMNG::GetIns()->stagegrids[a[i].y][a[i].x]->_color = { 0, 200, 200, 255 };
			break;
		case 2:
			StageMNG::GetIns()->stagegrids[a[i].y][a[i].x]->_color = { 255, 0, 0, 255 };
			break;
		case 3:
			StageMNG::GetIns()->stagegrids[a[i].y][a[i].x]->_color = { 0, 255, 0, 255 };
			break;
		case 4:
			StageMNG::GetIns()->stagegrids[a[i].y][a[i].x]->_color = { 255,0,204,255 };
			break;
		case 5:
			StageMNG::GetIns()->stagegrids[a[i].y][a[i].x]->_color = { 1, 0.5f, 0, 255 };
			break;
		case 6:
			StageMNG::GetIns()->stagegrids[a[i].y][a[i].x]->_color = { 0, 0, 255, 255 };
			break;
		case 7:
			StageMNG::GetIns()->stagegrids[a[i].y][a[i].x]->_color = { 255, 255, 0, 255 };
			break;
		default:
			break;
		}
	}

	//cout << "4" << endl;

	if (scenechange)
	{
		Director::GetIns()->SceneSet(new EndScene);
	}
}

void GameScene::Exit()
{
	StageMNG::GetIns()->DeleteStage();
	StageMNG::GetIns()->DeleteOtherStage();
	label->Delete_Label();
	delete label;
	nextlabel->Delete_Label();
	delete nextlabel;
	scorelabel->Delete_Label();
	delete scorelabel;
	cout << "EXIT" << endl;
}
