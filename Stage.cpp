#include "DXUT.h"
#include "Stage.h"

Grid::Grid()
{
	SetTexture(L"Block.png");
}


void StageMNG::CreateStage()
{
	stagegrids.resize(Stage_Height);
	for (int i = 0; i < Stage_Height; i++)
		stagegrids[i].resize(Stage_Width);
	for (float i = 0; i < Stage_Height; i++)
	{
		for (float j = 0; j < Stage_Width; j++)
		{
			Grid* grid = new Grid();
			grid->_position = { j * 50, i * 50 };
			stagegrids[i][j] = grid;
		}
	}
}

void StageMNG::CreateOtherStage()
{
	otherstagegrids.resize(10);
	for (int i = 0; i < 6; i++)
		otherstagegrids[i].resize(10);
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			Grid* grid = new Grid();
			otherstagegrids[i][j] = grid;
			grid->_position = { ((float)j * 50) + 700, ((float)i * 50) + 450 };
		}
	}
}

bool StageMNG::check()
{
	for (int i = 0; i < 4; i++)
	{
		if (a[i].x < 0 || a[i].x >= Stage_Width || a[i].y >= Stage_Height)
		{
			return false;
		}
		else if (stage[(int)a[i].y][(int)a[i].x] && a[i].y >= 0)
		{
			return false;
		}
	}
	return true;
}

void StageMNG::StartTetris()
{
	for (int i = 0; i < 4; i++)
	{
		a[i] = { 0,0 };
		b[i] = { 0,0 };
		c[i] = { 0,0 };
	}
	for (int i = 0; i < Stage_Height; i++)
		for (int j = 0; j < Stage_Width; j++)
			stage[i][j] = 0;
	nextnum = rand() % 7;
	int n = nextnum;
	nextnum = rand() % 7;
	for (int i = 0; i < 4; i++)
	{
		c[i].x = (tetrominosss[nextnum][i] % 2);
		c[i].y = (tetrominosss[nextnum][i] / 2);

		a[i].x = (tetrominosss[n][i] % 2) + 3;
		a[i].y = (tetrominosss[n][i] / 2) - 3;
	}
	nextcolornum = nextnum + 1;
	colornum = n + 1;
	dx = 0;
	rotate = false;
	GLOBAL::score = 0;
	GLOBAL::isgameover = false;
	if (otherstagegrids.size() != 10)
	{
		otherstagegrids.resize(10);
		for (int i = 0; i < 10; i++)
			otherstagegrids[i].resize(10);
	}
}

void StageMNG::CreateTetromino()
{
	if (!check())
	{
		cout << "새로나와" << endl;
		for (int i = 0; i < 4; i++) stage[(int)b[i].y][(int)b[i].x] = colornum;
		GLOBAL::score += 10;
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

void StageMNG::TetrominoMovement()
{
	for (int i = 0; i < 4; i++) { b[i] = a[i]; a[i].x += dx; }
	if (!check())
	{
		for (int i = 0; i < 4; i++)
		{
			if (a[i].y < 0) // 게임 진거임
			{
				//cout << otherstagegrids.size() << endl;
				//if (otherstagegrids.size() != 10)
				//{
				//	cout << "sibal 뭐야" << endl;
				//	otherstagegrids.resize(10);
				//	for (int j = 0; j < 10; j++)
				//	{
				//		otherstagegrids[j].resize(10);
				//	}
				//}
				GLOBAL::isgameover = true;
				cout << "end" << endl;
				return;
			}
			a[i] = b[i];
		}
	}

}

void StageMNG::TetrominoRotate()
{
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
}

void StageMNG::ReTextureTetris()
{
	for (int i = 0; i < Stage_Height; i++)
	{
		for (int j = 0; j < Stage_Width; j++)
		{
			if (stagegrids.size() != Stage_Height)
				return;
			stagegrids[i][j]->SetTexture(L"Block.png"); // 초기화
			stagegrids[i][j]->_color = { 255,255,255,255 };
		}
	}
	
}

void StageMNG::ReTextureOtherTetris()
{
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if (otherstagegrids.size() != 10)
				return;
			otherstagegrids[i][j]->SetTexture(L"Block.png");
			otherstagegrids[i][j]->_color = { 255,255,255,255 };
		}
	}
}

void StageMNG::CheckTetrisLine()
{
	int k = Stage_Height - 1;
	for (int i = Stage_Height - 1; i > 0; i--)
	{
		int count = 0;
		for (int j = 0; j < Stage_Width; j++)
		{
			if (stage[i][j]) count++;
			stage[k][j] = stage[i][j];
		}
		if (count < Stage_Width) k--;
		else
		{
			GLOBAL::score += 100;
		}
	}
}

void StageMNG::UpdateTetris()
{
	for (int i = 0; i < 4; i++)
	{
		b[i] = a[i];
		a[i].y++;

	}
}

void StageMNG::SetTetrisTexture()
{
	for (int i = 0; i < Stage_Height; i++)
	{
		for (int j = 0; j < Stage_Width; j++)
		{
			if (stage[i][j] == 0)
				continue;

			stagegrids[i][j]->SetTexture(L"poly.png");
			switch (stage[i][j])
			{
			case 1:
				stagegrids[i][j]->_color = { 0, 200, 200, 255 };
				break;
			case 2:
				stagegrids[i][j]->_color = { 255, 0, 0, 255 };
				break;
			case 3:
				stagegrids[i][j]->_color = { 0, 255, 0, 255 };
				break;
			case 4:
				stagegrids[i][j]->_color = { 255,0,204,255 };
				break;
			case 5:
				stagegrids[i][j]->_color = { 1, 0.5f, 0, 255 };
				break;
			case 6:
				stagegrids[i][j]->_color = { 0, 0, 255, 255 };
				break;
			case 7:
				stagegrids[i][j]->_color = { 255, 255, 0, 255 };
				break;
			default:
				break;
			}
		}
	}
	//cout << "3" << endl;

	for (int i = 0; i < 4; i++)
	{
		//cout << c[i].y + 1 << "  " << c[i].x + 2 << endl;
		
		if (a[i].y < 0)
		{
			continue;
		}
		stagegrids[a[i].y][a[i].x]->SetTexture(L"poly.png");
		switch (colornum)
		{
		case 1:
			stagegrids[a[i].y][a[i].x]->_color = { 0, 200, 200, 255 };
			break;
		case 2:
			stagegrids[a[i].y][a[i].x]->_color = { 255, 0, 0, 255 };
			break;
		case 3:
			stagegrids[a[i].y][a[i].x]->_color = { 0, 255, 0, 255 };
			break;
		case 4:
			stagegrids[a[i].y][a[i].x]->_color = { 255,0,204,255 };
			break;
		case 5:
			stagegrids[a[i].y][a[i].x]->_color = { 1, 0.5f, 0, 255 };
			break;
		case 6:
			stagegrids[a[i].y][a[i].x]->_color = { 0, 0, 255, 255 };
			break;
		case 7:
			stagegrids[a[i].y][a[i].x]->_color = { 255, 255, 0, 255 };
			break;
		default:
			break;
		}
	}

}

void StageMNG::SetOtherTetrisTexture()
{
	for (int i = 0; i < 4; i++)
	{
		if (otherstagegrids.size() != 10)
			return;
		otherstagegrids[c[i].y + 1][c[i].x + 2]->SetTexture(L"poly.png");
		switch (nextcolornum)
		{
		case 1:
			otherstagegrids[c[i].y + 1][c[i].x + 2]->_color = { 0, 200, 200, 255 };
			break;
		case 2:
			otherstagegrids[c[i].y + 1][c[i].x + 2]->_color = { 255, 0, 0, 255 };
			break;
		case 3:
			otherstagegrids[c[i].y + 1][c[i].x + 2]->_color = { 0, 255, 0, 255 };
			break;
		case 4:
			otherstagegrids[c[i].y + 1][c[i].x + 2]->_color = { 255,0,204,255 };
			break;
		case 5:
			otherstagegrids[c[i].y + 1][c[i].x + 2]->_color = { 1, 0.5f, 0, 255 };
			break;
		case 6:
			otherstagegrids[c[i].y + 1][c[i].x + 2]->_color = { 0, 0, 255, 255 };
			break;
		case 7:
			otherstagegrids[c[i].y + 1][c[i].x + 2]->_color = { 255, 255, 0, 255 };
			break;
		default:
			break;
		}
	}
}

void StageMNG::DeleteStage()
{
	for (int i = 0; i < Stage_Height; i++)
	{
		for (auto it : stagegrids[i])
		{
			delete it;
		}
		stagegrids[i].clear();

	}
	stagegrids.clear();

	//for (int i = 0; i < Stage_Height; i++)
	//{
	//	for (int j = 0; j < Stage_Width; j++)
	//	{
	//		delete stagegrids[i][j];
	//	}
	//}
	//stagegrids.clear();
}

void StageMNG::DeleteOtherStage()
{
	try
	{
		for (int i = 0; i < 10; i++)
		{
			for (auto it : otherstagegrids[i])
			{
				if (it)
					delete it;
			}
			otherstagegrids[i].clear();
		}
		otherstagegrids.clear();
	}
	catch(out_of_range otherstagegrids)
	{
		exit(1);
	}
}
