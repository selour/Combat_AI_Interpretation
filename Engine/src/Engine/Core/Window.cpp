#include "stdafx.h"
#include "Window.h"
#include "Platform/GLFW/GLFWWindow.h"
namespace Engine
{
	Window* Window::Create(const WindowProps& props)
	{
		switch (PlatformAPI::GetAPI())
		{
		case PlatformAPI::API::None:
			ENGINE_ASSERT(false, "PlatformAPI::None is currently not supported!");
			return nullptr;
		case PlatformAPI::API::GLFW:
			return new GLFWWindow(props);
		}
		ENGINE_ASSERT(false, "Unknown PlatformAPI!");
		return nullptr;
	}
}