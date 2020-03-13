#pragma once
#include "Scene.h"
#include "Director.h"
#include "Label.h"
#include "GameScene.h"
class MainScene :
	public Scene
{
public:
	void Init() override;
	void Update() override;
	void Exit() override;
	Label* start;
	Label* exit;
	Label* main;
};

