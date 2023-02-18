#include "stdafx.h"
#include "RendererCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"
namespace Engine
{
	RendererAPI* RendererCommand::s_RendererAPI = Creat();
	RendererAPI* RendererCommand::Creat()
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None:
			ENGINE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLRendererAPI();
		}
		ENGINE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}