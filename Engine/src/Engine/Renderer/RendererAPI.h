#pragma once
#include <glm/glm.hpp>
#include "VertexArray.h"

enum StencilFuncMode
{
	NEVER = 0,
	LESS = 1,
	EQUAL = 2,
	LEQUAL = 3,
	GREATER = 4,
	NOTEQUAL = 5,
	GEQUAL = 6,
	ALWAYS = 7
};
namespace Engine
{
	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0,
			OpenGL = 1

		};
		virtual void Init() = 0;
		virtual void SetViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height) = 0;
		virtual void SetClearColor(const glm::vec4 color) = 0;
		virtual void ClearColorBuffer() = 0;
		virtual void ClearDepthBuffer() = 0;
		virtual void ClearStencilBuffer() = 0;
		virtual void Clear() = 0;
		virtual void EnableDepthTest() = 0;
		virtual void DisableDepthTest() = 0;
		virtual void SetStencilMask(int value) = 0;
		virtual void SetStencilFunc(StencilFuncMode func, int ref, unsigned int mask) = 0;
		virtual void Draw(const std::shared_ptr<VertexArray>& vertexArray) = 0;
		virtual void DrawInstanced(const std::shared_ptr<VertexArray>& vertexArray, unsigned int count) = 0;
		inline static API GetAPI() { return s_API; }
	private:
		static API s_API;
	};
}


