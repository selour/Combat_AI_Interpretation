#include "stdafx.h"
#include "Renderer.h"
#include "Shader.h"
#include "Platform/OpenGL/OpenGLShader.h"
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
	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, glm::mat4 model)
	{	
		shader->Use();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->SetMatrix4("u_ViewProjection", s_SceneData->ViewProjectionMatrix, true);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->SetMatrix4("u_Model", model, true);
		RendererCommand::Draw(vertexArray);
	}
}