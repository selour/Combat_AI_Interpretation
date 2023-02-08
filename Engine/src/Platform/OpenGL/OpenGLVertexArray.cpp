#include "stdafx.h"
#include <glad/glad.h>  
#include "OpenGLVertexArray.h"

namespace Engine
{
	static unsigned int ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:		return GL_FLOAT;
		case ShaderDataType::Float2:	return GL_FLOAT;
		case ShaderDataType::Float3:	return GL_FLOAT;
		case ShaderDataType::Float4:	return GL_FLOAT;
		case ShaderDataType::Mat3:		return GL_FLOAT;
		case ShaderDataType::Mat4:		return GL_FLOAT;
		case ShaderDataType::Int:		return GL_INT;
		case ShaderDataType::Int2:		return GL_INT;
		case ShaderDataType::Int3:		return GL_INT;
		case ShaderDataType::Int4:		return GL_INT;
		case ShaderDataType::Bool:		return GL_BOOL;
		}

		ENGINE_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}
	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_VAO);
	}
	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_VAO);
	}
	void OpenGLVertexArray::UnBind() const
	{
		glBindVertexArray(0);
	}
	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		
		
		ENGINE_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");
		
		
		glBindVertexArray(m_VAO);
		vertexBuffer->Bind();

		const auto layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(element.Index);
			glVertexAttribPointer(element.Index,
				element.GetCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized,
				layout.GetStride(),
				(const void*)element.Offset);
			glVertexAttribDivisor(element.Index, element.AttributeDivisor);
		}
		m_VBOs.push_back(vertexBuffer);
	}
	void OpenGLVertexArray::SetElementBuffer(const std::shared_ptr<ElementBuffer>& elementBuffer)
	{
		glBindVertexArray(m_VAO);
		elementBuffer->Bind();
		m_EBO = elementBuffer;
	}
}