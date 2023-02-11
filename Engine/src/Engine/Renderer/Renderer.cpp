#include "stdafx.h"
#include "Renderer.h"
#include "Renderer2D.h"
#include "RendererPostProcessing.h"
#include "Shader.h"

namespace Engine
{
	Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData();
	void Renderer::Init()
	{
		RendererCommand::Init();
		Renderer2D::Init();
		RendererPostProcessing::Init();
	}
	void Renderer::OnWindowResize(unsigned int width, unsigned int height)
	{
		RendererCommand::SetViewport(0, 0, width, height);
	}
	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}
	void Renderer::EndScene()
	{
	}
	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, glm::mat4 model)
	{	
		shader->Use();
		shader->SetMatrix4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
		shader->SetMatrix4("u_Model", model);
		RendererCommand::Draw(vertexArray);
	}
}