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
	void CreateStage();
	void CreateOtherStage();
	void DeleteStage();
	void DeleteOtherStage();
};
