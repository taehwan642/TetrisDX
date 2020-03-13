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
	// tetrominos 옮기고
	// a, b, c 옮기고
	// 전체 개편 해야할듯
	void CreateStage();
	void CreateOtherStage();
	void DeleteStage();
	void DeleteOtherStage();
};
