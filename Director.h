#pragma once
#include "Singleton.h"
#include "Scene.h"
class Director : public Singleton<Director>
{
private:
	Scene* currentScene;
public:
	void DirectorInit();
	void SceneSet(Scene* s);
	void SceneUpdate();
};

