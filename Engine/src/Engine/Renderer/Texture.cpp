#include "stdafx.h"
#include "Texture.h"
#include "Engine/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"
namespace Engine
{

	Texture2D* Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetRendererAPI())
		{
		case RendererAPI::API::None:
			ENGINE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLTexture2D(path);
		}
		ENGINE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}
