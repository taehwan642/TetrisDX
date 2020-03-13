#include "DXUT.h"
#include "Director.h"

void Director::DirectorInit()
{
	currentScene = nullptr;
}

void Director::SceneSet(Scene* s)
{
	if (currentScene != nullptr && s != nullptr)
		currentScene->Exit();
	if (s != nullptr)
	{
		currentScene = s;
		currentScene->Init();
	}
}

void Director::SceneUpdate()
{
	if (currentScene != nullptr)
	{
		currentScene->Update();
		Renderer::GetIns()->Render();
	}
	else
		cout << "null" << endl;
}
