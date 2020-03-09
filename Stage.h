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
	void CreateStage();
	void DeleteStage();
};
