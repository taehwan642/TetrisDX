#include "DXUT.h"
#include "Label.h"

void Label::Create_Label(int v)
{
	Delete_Label();
	Addpos = 0;

	for (auto it : to_wstring(v))
	{
		Sprite* s = new Sprite;
		s->_scale = _scale;
		s->_isUI = true;
		s->SetTexture(L"font/" + to_wstring(it - 48) + L".png");
		s->_position = { Addpos * s->_scale.x + _position.x,_position.y };
		Addpos += labeldistance;
		labels.push_back(s);
	}
}

void Label::Create_Label(int v, Vec2 vec)
{
	Delete_Label();
	Addpos = 0;
	_position = vec;
	for (auto it : to_wstring(v))
	{
		Sprite* s = new Sprite();
		s->_scale = _scale;
		s->_isUI = true;
		s->SetTexture(L"font/" + to_wstring(it - 48) + L".png");
		s->_position = { Addpos + _position.x, _position.y };
		Addpos += labeldistance;
		labels.push_back(s);
	}
}


void Label::Create_Label(string s)
{
	Delete_Label();
	Addpos = 0;
	for (auto it : s)
	{
		Sprite* s = new Sprite;
		s->_scale = _scale;
		s->_isUI = true;
		s->SetTexture(L"font/" + to_wstring(it) + L".png");
		s->_position = { Addpos * s->_scale.x + _position.x,_position.y };
		Addpos += labeldistance;
		labels.push_back(s);
	}
}

void Label::Create_Label(string s, Vec2 vec)
{
	Delete_Label();
	Addpos = 0;
	_position = vec;
	for (auto it : s)
	{
		Sprite* s = new Sprite;
		s->_scale = _scale;
		s->_isUI = true;
		s->SetTexture(L"font/" + to_wstring(it) + L".png");
		s->_position = { Addpos * s->_scale.x + _position.x,_position.y };
		Addpos += labeldistance;
		labels.push_back(s);
	}
}

void Label::Delete_Label()
{
	for (auto it : labels)
	{
		delete it;
	}
	labels.clear();
}
