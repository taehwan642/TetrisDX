#pragma once
class Node
{
public:
	Node();
	virtual ~Node() {};
	Vec2 _position;
	Vec2 _scale;
	Vec2 _pivot;
	Vec2 _nv;
	Color _color;
	int _layer;
	float _rotation;
	bool _visible;
	bool _isUI;
	D3DXMATRIX GetMatrix();
	virtual void Update() {};
	virtual void Draw() {};
};

