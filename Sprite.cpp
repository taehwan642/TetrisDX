#include "DXUT.h"
#include "Sprite.h"

Sprite::Sprite()
{
	_texture = nullptr;
	_sprite = nullptr;
	D3DXCreateSprite(DXUTGetD3D9Device(), &_sprite);
}

Sprite::~Sprite()
{
	Renderer::GetIns()->RemoveRenderTargets(this);
}

void Sprite::SetTexture(wstring path)
{
	_texture = TextureMNG::GetIns()->LoadTexture(path);
	AddRenderTarget();
}

void Sprite::AddRenderTarget()
{
	Renderer::GetIns()->AddRenderTargets(this);
}

RECT Sprite::GetRect()
{
	RECT r = { 0,0,0,0 };
	r.right = _position.x + (_texture->_info.Width / 2 * _scale.x);
	r.left = _position.x - (_texture->_info.Width / 2 * _scale.x);
	r.top = _position.y - (_texture->_info.Height / 2 * _scale.y);
	r.bottom = _position.y + (_texture->_info.Height / 2 * _scale.y);
	return r;
}

void Sprite::Draw()
{
	if (!_visible)
		return;
	if (_texture == nullptr)
		return;
	_isUI ? _sprite->Begin(D3DXSPRITE_ALPHABLEND) : _sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE);
	_sprite->SetTransform(&GetMatrix());
	Vec3 center = { _pivot.x * _texture->_info.Width,_pivot.y * _texture->_info.Height, 0 };
	_sprite->Draw(_texture->_texture, nullptr, &center, nullptr, _color);
	_sprite->End();
}
