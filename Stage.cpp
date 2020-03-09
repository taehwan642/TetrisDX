#include "DXUT.h"
#include "Stage.h"

Grid::Grid()
{
	SetTexture(L"Block.png");
}

void StageMNG::CreateStage()
{
	stagegrids.resize(Stage_Height + 30);
	for (int i = 0; i < Stage_Width + 30; i++)
		stagegrids[i].resize(Stage_Width + 30);
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

void StageMNG::DeleteStage()
{
	for (int i = 0; i < Stage_Height; i++)
	{
		for (int j = 0; j < Stage_Width; j++)
		{
			delete stagegrids[i][j];
		}
	}
	stagegrids.clear();
}
