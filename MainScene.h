#pragma once
#include "Scene.h"
#include "Director.h"
#include "GameScene.h"
class MainScene :
	public Scene
{
	void Init() override;
	void Update() override;
	void Exit() override;
};

