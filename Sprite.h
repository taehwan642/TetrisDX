#pragma once
#include "Director.h"
#include "Node.h"
#include "Texture.h"
#include "Renderer.h"

class Sprite : public Node
{
public:
	Texture* _texture;
	LPD3DXSPRITE _sprite;
	Sprite();
	~Sprite();
	void SetTexture(wstring path);
	void AddRenderTarget();
	RECT GetRect();
	void Draw() override;
};

