#include "DXUT.h"
#include "GameScene.h"
// 해야할거 
// 4. 메인 씬 만들기
// 5. 소리 띄우기 
bool GameScene::check()
{
	for (int i = 0; i < 4; i++)
	{
		if (a[i].x < 0 || a[i].x >= Stage_Width || a[i].y >= Stage_Height)
		{
			return false;
		}
		else if (field[(int)a[i].y][(int)a[i].x])
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
		a[i].y = (tetrominosss[n][i] / 2) - 1;
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

	// 다음에 나올 애 ㅅ설정
	nextcolornum = nextnum + 1;
	colornum = n + 1;
	dx = 0;
	rotate = false;
	delay = 0.3f;
	label = new Label();
	score = 0;
	label->_scale = { 2,2 };
	label->labeldistance = 50;
	label->Create_Label(score, { 600,200 });
	scenechange = false;
}

void GameScene::Update()
{
	for (int i = 0; i < Stage_Height; i++)
	{
		for (int j = 0; j < Stage_Width; j++)
		{
			StageMNG::GetIns()->stagegrids[i][j]->SetTexture(L"Block.png"); // 초기화
			StageMNG::GetIns()->stagegrids[i][j]->_color = { 255,255,255,255 };
		}
	}
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			StageMNG::GetIns()->otherstagegrids[i][j]->SetTexture(L"Block.png");
			StageMNG::GetIns()->otherstagegrids[i][j]->_color = { 255,255,255,255 };

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
		Director::GetIns()->SceneSet(new MainScene);
	}
		//for (int i = 0; i < Stage_Height; i++)
		//{
		//	for (int j = 0; j < Stage_Width; j++)
		//	{
		//		cout << field[i][j] << " ";
		//	}
		//	cout << endl;
		//}
	
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
		} // 반대로 회전행렬 입히기 Q, E 사용
		if (!check()) for (int i = 0; i < 4; i++) a[i] = b[i];
	}
	time += GLOBAL::deltatime;
	if (time > delay)
	{
		for (int i = 0; i < 4; i++) { b[i] = a[i]; a[i].y++; }
		if (!check())
		{
			for (int i = 0; i < 4; i++) field[(int)b[i].y][(int)b[i].x] = colornum; // 조종하는 블록 맵에 설치 (놓아졌을때)
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
				a[i].y = (tetrominosss[n][i] / 2) - 1;
			}
		}
		delay = 0.3f;
		time = 0;
	}
	dx = 0;
	rotate = false;
	for (int i = 0; i < 4; i++)
		if (field[(int)b[i].x][(int)b[i].y])
		{
			cout << "??" << endl;
			// 꼇다. 패배한거임.
			//Director::GetIns()->SceneSet(new MainScene);
		}
	
	int k = Stage_Height - 1;
	for (int i = Stage_Height - 1; i > 0; i--)
	{
		int count = 0;
		for (int j = 0; j < Stage_Width; j++)
		{
			if (field[i][j]) count++;
				// 점수!
			field[k][j] = field[i][j];
		}
		if (count < Stage_Width) k--; 
		else
		{
			score += 250;
			label->Create_Label(score, { 600,200 });
		}
	}


	for (int i = 0; i < Stage_Height; i++)
	{
		for (int j = 0; j < Stage_Width; j++)
		{
			if (field[i][j] == 0)
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
	for (int i = 0; i < 4; i++)
	{
		if (a[i].y < 0)
		{
			return;
		}
		if (scenechange)
			return;
		//if (StageMNG::GetIns()->stagegrids[a[i].y][a[i].x] == nullptr)
		//	return;
		StageMNG::GetIns()->stagegrids[a[i].y][a[i].x]->SetTexture(L"poly.png");
		StageMNG::GetIns()->otherstagegrids[c[i].y + 1][c[i].x + 2]->SetTexture(L"poly.png");
		//cout << colornum << endl;
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
}

void GameScene::Exit()
{
	//StageMNG::GetIns()->DeleteStage();
	//StageMNG::GetIns()->DeleteOtherStage();
	label->Delete_Label();
	delete label;
	cout << "EXIT" << endl;
}
