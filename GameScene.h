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
    bool check();
	void Init() override;
	void Update() override;
	void Exit() override;
    Label* label;
    Label* scorelabel;
    Label* nextlabel;
    int score;
    float time = 0;
    int field[Stage_Height][Stage_Width] = {0};
    Vec2 a[4], b[4];
    Vec2 c[4];
    int nextnum;
    int currnum;
    int colornum;
    int nextcolornum;
    int dx;
    float delay;
    bool rotate;
    bool scenechange;
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
};

