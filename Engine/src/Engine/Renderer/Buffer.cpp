#include "stdafx.h"
#include "Buffer.h"
#include "Engine/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"
namespace Engine
{	
	
	std::shared_ptr<VertexBuffer> VertexBuffer::Create(float* vertices, unsigned int size)
	{
		switch (Renderer::GetRendererAPI())
		{
		case RendererAPI::API::None:
			ENGINE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLVertexBuffer>(vertices, size);
		}
		ENGINE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
	std::shared_ptr<ElementBuffer> ElementBuffer::Create(unsigned int* indices, unsigned int count)
	{
		
		switch (Renderer::GetRendererAPI())
		{
		case RendererAPI::API::None:
			ENGINE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLElementBuffer>(indices, count);
		}
		ENGINE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
	


}

