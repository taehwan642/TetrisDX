#pragma once
#include "Scene.h"
#include "MainScene.h"
#include "EndScene.h"
#include "Sprite.h"
#include "Camera.h"
#include "Stage.h"
#include "Label.h"  

class GameScene :
	public Scene
{
public:
	void Init() override;
	void Update() override;
	void Exit() override;
    Label* label;
    Label* scorelabel;
    Label* nextlabel;
    float time = 0;
    float delay;
};

