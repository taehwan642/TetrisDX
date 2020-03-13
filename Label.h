#pragma once
#include "Sprite.h"
class Label :
	public Sprite
{
public:
	int Addpos;
	int labeldistance = 100;
	vector<Sprite*> labels;
	void Create_Label(int v);
	void Create_Label(int v, Vec2 vec);
	void Create_Label(string s);
	void Create_Label(string s, Vec2 vec);
	void Delete_Label();
};

