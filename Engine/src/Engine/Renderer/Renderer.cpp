#include "stdafx.h"
#include "Renderer.h"

namespace Engine
{
	void Renderer::BeginScene()
	{
	}
	void Renderer::EndScene()
	{
	}
	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray)
	{
		RendererCommand::Draw(vertexArray);
	}
}