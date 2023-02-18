#include "stdafx.h"
#include "GLFWAPI.h"
#include <GLFW/glfw3.h>
namespace Engine
{
	float GLFW_API::GetTime()
	{
		return (float)glfwGetTime();
	}
}