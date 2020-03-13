#pragma once
#include "Scene.h"
#include "Label.h"
#include "MainScene.h"
class EndScene :
	public Scene
{
public:
	void Init() override;
	void Update() override;
	void Exit() override;
	Label* label;
	Label* scorelabel;
	Label* rest;
};

