#include "stdafx.h"
#include "Buffer.h"
#include "Engine/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"
namespace Engine
{	
	
	VertexBuffer* Engine::VertexBuffer::Create(float* vertices, unsigned int size)
	{
		switch (Renderer::GetRendererAPI())
		{
		case RendererAPI::None:
			ENGINE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::OpenGL:
			return new OpenGLVertexBuffer(vertices, size);
		}
		ENGINE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
	ElementBuffer* Engine::ElementBuffer::Create(unsigned int* indices, unsigned int count)
	{
		
		switch (Renderer::GetRendererAPI())
		{
		case RendererAPI::None:
			ENGINE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::OpenGL:
			return new OpenGLElementBuffer(indices, count);
		}
		ENGINE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
	


}

