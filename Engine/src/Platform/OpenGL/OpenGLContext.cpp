#include "stdafx.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "OpenGLContext.h"

Engine::OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
	:m_windowHandle(windowHandle)
{
	ENGINE_CORE_ASSERT(windowHandle, "Window handle is null");
}

void Engine::OpenGLContext::Init()
{ 
	glfwMakeContextCurrent(m_windowHandle);
	int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	ENGINE_CORE_ASSERT(status, "Fail to initialize Glad!");


	ENGINE_CORE_INFO("OpenGL Info:");
	ENGINE_CORE_INFO("	Vendor:\t{0}", (const char*)glGetString(GL_VENDOR));
	ENGINE_CORE_INFO("	Renderer:\t{0}", (const char*)glGetString(GL_RENDERER));
	ENGINE_CORE_INFO("	Version:\t{0}", (const char*)glGetString(GL_VERSION));
}

void Engine::OpenGLContext::SwapBuffers()
{
	glfwSwapBuffers(m_windowHandle);
}
