#pragma once
#include "Engine/Renderer/RendererAPI.h"

namespace Engine
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void Init() override;
		virtual void SetViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height) override;
		virtual void SetClearColor(const glm::vec4 color) override;
		virtual void Clear() override;
		virtual void SetStencilMask(int value) override;
		virtual void SetStencilFunc(StencilFuncMode func, int ref, unsigned int mask) override;
		virtual void Draw(const std::shared_ptr<VertexArray>& vertexArray) override;
		virtual void DrawInstanced(const std::shared_ptr<VertexArray>& vertexArray, unsigned int count) override;
	};


}

