#include "DXUT.h"
#include "Node.h"

Node::Node()
{
	_position = { 0,0 };
	_scale = { 1,1 };
	_pivot = { 0.5f,0.5f };
	_nv = { 0.5f,0.5f };
	_color = 0xffffffff;
	_layer = 0;
	_rotation = 0;
	_visible = true;
	_isUI = false;
}

D3DXMATRIX Node::GetMatrix()
{
	D3DXMATRIX m;
	D3DXMatrixIdentity(&m);
	D3DXMatrixTransformation2D(&m, nullptr, 0, &_scale, nullptr, _rotation, &_position);
	return m;
}
