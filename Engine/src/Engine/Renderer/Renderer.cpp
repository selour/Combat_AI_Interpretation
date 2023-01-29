#include "stdafx.h"
#include "Renderer.h"
#include "Shader.h"
namespace Engine
{
	Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData();
	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}
	void Renderer::EndScene()
	{
	}
	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader)
	{
		shader->Use();
		shader->SetMatrix4("u_ViewProjection", s_SceneData->ViewProjectionMatrix, true);
		RendererCommand::Draw(vertexArray);
	}
}