#pragma once
#include "Engine/Renderer/VertexArray.h"
namespace Engine
{
	class OpenGLVertexArray : public Engine::VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray() {}

		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
		virtual void SetElementBuffer(const std::shared_ptr<ElementBuffer>& elementBuffer) override;
	
		virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const { return m_VBOs; }
		virtual const std::shared_ptr<ElementBuffer>& GetElementBuffer() const { return m_EBO; }
	
	private:
		unsigned int m_VAO;
		std::vector<std::shared_ptr<VertexBuffer>> m_VBOs;
		std::shared_ptr<ElementBuffer> m_EBO;
	};
}


