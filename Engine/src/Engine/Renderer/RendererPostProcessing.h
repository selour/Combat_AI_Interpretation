#pragma once
#include "Shader.h"
#include "FrameBuffer.h"
namespace Engine
{
	class RendererPostProcessing
	{
	public:
		static void Init();
		static void Shutdown();
		static void Draw(const std::shared_ptr<FrameBuffer> frameBuffer, const std::shared_ptr<Shader> shader);
	};
}

