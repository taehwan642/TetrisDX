#pragma once
#include "Sprite.h"
class Grid :
	public Sprite
{
public:
	Grid();
};

class StageMNG :public Singleton<StageMNG>
{
public:
	vector<vector<Grid*>> stagegrids;
	vector<vector<Grid*>> otherstagegrids;
	vector<Grid*> otherstage;
	// field 옮기고
	int stage[Stage_Height][Stage_Width] = { 0 };
	int currnum;
	int nextnum;
	int colornum;
	int nextcolornum;
	int dx;
	bool rotate;
	int tetrominosss[7][4] =
	{
		1,3,5,7, // I
		2,4,5,7, // Z
		3,5,4,6, // S
		3,5,4,7, // T
		2,3,5,7, // L
		3,5,7,6, // J
		2,3,4,5, // O
	};
	Vec2 a[4], b[4];
	Vec2 c[4];
	// 전체 개편 해야할듯
	void CreateStage();		
	void CreateOtherStage();
	bool check();
	void StartTetris();
	void CreateTetromino();
	void TetrominoMovement();
	void TetrominoRotate();
	void ReTextureTetris();
	void ReTextureOtherTetris();
	void CheckTetrisLine();
	void UpdateTetris();
	void SetTetrisTexture();
	void SetOtherTetrisTexture();
	void DeleteStage();
	void DeleteOtherStage();
};
