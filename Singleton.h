#pragma once
template <class T>
class Singleton
{
private:
	static T* instance;
public:
	static T* GetIns()
	{
		if (instance == nullptr)
			instance = new T();
		return instance;
	}
};

template <class T> T* Singleton<T>::instance = nullptr;

class GLOBAL
{
public:
	static float deltatime;
	static float timescale;
	static int score;
	static bool isgameover;
};