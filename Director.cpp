#include "DXUT.h"
#include "Director.h"

void Director::DirectorInit()
{
	currentScene = nullptr;
}

void Director::SceneSet(Scene* s)
{
	if (currentScene != nullptr)
		currentScene->Exit();
	currentScene = s;
	currentScene->Init();
}

void Director::SceneUpdate()
{
	if(currentScene)
		currentScene->Update();
	Renderer::GetIns()->Render();
}
