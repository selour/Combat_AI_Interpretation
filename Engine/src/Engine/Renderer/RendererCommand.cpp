#include "stdafx.h"
#include "RendererCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"
namespace Engine
{
	RendererAPI* RendererCommand::s_RendererAPI = new OpenGLRendererAPI();
}