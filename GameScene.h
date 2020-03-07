#pragma once
#include "Scene.h"
#include "Sprite.h"
#include "Camera.h"
#include "Tetromino.h"
class GameScene :
	public Scene
{
public:
	void Init() override;
	void Update() override;
	void Exit() override;

};

