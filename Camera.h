#pragma once
#include "Singleton.h"
class Camera :
	public Singleton<Camera>
{
private:
	D3DXMATRIX OM;
	D3DXMATRIX IM;
	D3DXMATRIX VM;
	Vec2 _campos;
	float _camerasize;
public:

	void CameraInit();
	void Update();
	void SetPos(Vec2 v) { _campos.x = v.x; _campos.y = v.y; };
	Vec2 GetPos() const { return _campos; };
	void SetSize(float f) { _camerasize = f; };
	float GetSize() const { return _camerasize; };
};

