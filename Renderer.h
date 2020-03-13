#pragma once
#include "Singleton.h"
#include "Node.h"
class Renderer :
	public Singleton<Renderer>
{
private:
	static bool Comp(Node* a, Node* b);
public:
	list<Node*> _rendertargets;
	void AddRenderTargets(Node* n);
	void RemoveRenderTargets(Node* n);
	void Render();
};

