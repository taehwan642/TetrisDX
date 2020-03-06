#pragma once
#include "Singleton.h"
class Texture
{
public:
	D3DXIMAGE_INFO _info;
	wstring _filename;
	LPDIRECT3DTEXTURE9 _texture;
};

class TextureMNG : public Singleton<TextureMNG>
{
private:
	list<Texture*> _texturepool;
public:
	Texture* LoadTexture(wstring path);
};