#include "DXUT.h"
#include "Renderer.h"

void Renderer::AddRenderTargets(Node* n)
{
	if (find(_rendertargets.begin(), _rendertargets.end(), n) != _rendertargets.end())
		return;

	_rendertargets.push_back(n);
	_rendertargets.sort(Comp);
}

void Renderer::RemoveRenderTargets(Node* n)
{
	_rendertargets.remove(n);
}

void Renderer::Render()
{
	for (auto it : _rendertargets)
	{
		it->Draw();
		it->Update();
	}
}

bool Renderer::Comp(Node* a, Node* b)
{
	return a->_layer < b ->_layer;
}
