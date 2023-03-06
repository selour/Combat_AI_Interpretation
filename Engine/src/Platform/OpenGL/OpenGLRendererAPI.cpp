#include "stdafx.h"
#include <glad/glad.h>
#include "OpenGLRendererAPI.h"

namespace Engine
{
	void OpenGLRendererAPI::Init()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//glEnable(GL_DEPTH_TEST);

	}
	void OpenGLRendererAPI::SetViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height)
	{
		glViewport(x, y, width, height);

	}
	void OpenGLRendererAPI::SetClearColor(const glm::vec4 color)
	{
		glColorMask(TRUE, TRUE, TRUE, TRUE);
		glClearColor(color.r, color.g, color.b, color.a);
	}
	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	void OpenGLRendererAPI::Draw(const std::shared_ptr<VertexArray>& vertexArray)
	{
		unsigned int indexCount = vertexArray->GetElementBuffer()->GetCount();
		glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);

		glBindTexture(GL_TEXTURE_2D, 0);
	}
	void OpenGLRendererAPI::DrawInstanced(const std::shared_ptr<VertexArray>& vertexArray, unsigned int count)
	{
		unsigned int indexCount = vertexArray->GetElementBuffer()->GetCount();
		glDrawElementsInstanced(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr, count);

		glBindTexture(GL_TEXTURE_2D, 0);
	
	}
}