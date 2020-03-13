#pragma once
#include "Scene.h"
#include "Label.h"
class EndScene :
	public Scene
{
public:
	void Init() override;
	void Update() override;
	void Exit() override;
	Label* label;
};

