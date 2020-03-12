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
			grid->_position = { ((float)j * 50) + 700, ((float)i * 50) + 450};
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

void StageMNG::DeleteOtherStage()
{
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			delete otherstagegrids[i][j];
		}
	}
	otherstagegrids.clear();
}
