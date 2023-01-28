#include "stdafx.h"
#include <glad/glad.h>
#include "OpenGLRendererAPI.h"

namespace Engine
{
	void OpenGLRendererAPI::SetClearColor(const glm::vec4 color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}
	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	void OpenGLRendererAPI::Draw(const std::shared_ptr<VertexArray>& vertexArray)
	{
		glDrawElements(GL_TRIANGLES, vertexArray->GetElementBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
}