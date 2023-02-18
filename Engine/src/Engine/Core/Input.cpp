#include "stdafx.h"
#include "Input.h"
#include "PlatformAPI.h"
#include "Platform/GLFW/GLFWInput.h"
namespace Engine
{
	
	Input* Input::s_Instance = Input::Create();
	Input* Input::Create()
	{
		switch (PlatformAPI::GetAPI())
		{
		case PlatformAPI::API::None:
			ENGINE_ASSERT(false, "PlatformAPI::None is currently not supported!");
			return nullptr;
		case PlatformAPI::API::GLFW:
			return new GLFWInput();
		}
		ENGINE_ASSERT(false, "Unknown PlatformAPI!");
		return nullptr;
	}
}