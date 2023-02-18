#include "stdafx.h"
#include "PlatformCommand.h"
#include "Platform/GLFW/GLFWAPI.h"
namespace Engine
{
	PlatformAPI* PlatformCommand::s_PlatformAPI = PlatformCommand::Creat();
	PlatformAPI* Engine::PlatformCommand::Creat()
	{
		switch (PlatformAPI::GetAPI())
		{
		case PlatformAPI::API::None:
			ENGINE_ASSERT(false, "PlatformAPI::None is currently not supported!");
			return nullptr;
		case PlatformAPI::API::GLFW:
			return new GLFW_API();
		}
		ENGINE_ASSERT(false, "Unknown PlatformAPI!");
		return nullptr;
	}
}

