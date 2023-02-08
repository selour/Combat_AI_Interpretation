#include "stdafx.h"
#include "Texture.h"
#include "Engine/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"
namespace Engine
{
	std::shared_ptr<Texture2D> Texture2D::Create()
	{
		switch (Renderer::GetRendererAPI())
		{
		case RendererAPI::API::None:
			ENGINE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLTexture2D>();
		}
		ENGINE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
	std::shared_ptr<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetRendererAPI())
		{
		case RendererAPI::API::None:
			ENGINE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLTexture2D>(path);
		}
		ENGINE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	std::shared_ptr<Texture2DArray> Texture2DArray::Create()
	{
		switch (Renderer::GetRendererAPI())
		{
		case RendererAPI::API::None:
			ENGINE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLTexture2DArray>();
		}
		ENGINE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	std::shared_ptr<Texture2DArray> Texture2DArray::Create(const std::string& path, unsigned int xIndex, unsigned int yIndex)
	{
		switch (Renderer::GetRendererAPI())
		{
		case RendererAPI::API::None:
			ENGINE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLTexture2DArray>(path, xIndex, yIndex);
		}
		ENGINE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}
