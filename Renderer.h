#pragma once
#include "Singleton.h"
#include "Node.h"
class Renderer :
	public Singleton<Renderer>
{
private:
	list<Node*> _rendertargets;
	static bool Comp(Node* a, Node* b);
public:
	void AddRenderTargets(Node* n);
	void RemoveRenderTargets(Node* n);
	void Render();
};

