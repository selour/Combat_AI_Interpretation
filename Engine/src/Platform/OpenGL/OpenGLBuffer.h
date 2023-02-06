#pragma once
#include "Engine/Renderer/Buffer.h"
namespace Engine
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, unsigned int size);
		OpenGLVertexBuffer(unsigned int size);
		virtual ~OpenGLVertexBuffer() override;

		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual void SetData(const void* data, unsigned int size) override;

		virtual const BufferLayout& GetLayout() const override { return m_Layout; }
		virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }
	private:
		unsigned int m_VBO;
		BufferLayout m_Layout;
	};

	class OpenGLElementBuffer : public ElementBuffer
	{
	public:
		OpenGLElementBuffer(unsigned int* indices, unsigned int count);
		virtual ~OpenGLElementBuffer() override;
		
		virtual void Bind() const override;
		virtual void UnBind() const override;
		virtual unsigned int GetCount() const override { return m_Count; }
	private:
		unsigned int m_EBO;
		unsigned int m_Count;
	};





}

