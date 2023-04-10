#include "stdafx.h"
#include "FrameBuffer.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLFrameBuffer.h"
namespace Engine
{
	std::shared_ptr<FrameBuffer> FrameBuffer::Create(const FrameBufferSpecification& spec)
	{
		switch (Renderer::GetRendererAPI())
		{
		case RendererAPI::API::None:
			ENGINE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLFrameBuffer>(spec);
		}
		ENGINE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
	std::shared_ptr<MRTFrameBuffer> MRTFrameBuffer::Create(const FrameBufferSpecification& spec, unsigned amount)
	{
		switch (Renderer::GetRendererAPI())
		{
		case RendererAPI::API::None:
			ENGINE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLMRTFrameBuffer>(spec, amount);
		}
		ENGINE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}