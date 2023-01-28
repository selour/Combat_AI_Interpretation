#include "stdafx.h"
#include "Renderer.h"

namespace Engine
{
	void Renderer::BeginScene()
	{
		RendererCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1));
		RendererCommand::Clear();
	}
	void Renderer::EndScene()
	{
	}
	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray)
	{
		RendererCommand::Draw(vertexArray);
	}
}