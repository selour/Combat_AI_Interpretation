#pragma once
#include <glm/glm.hpp>
#include "VertexArray.h"
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
		virtual void Clear() = 0;

		virtual void Draw(const std::shared_ptr<VertexArray>& vertexArray, unsigned int count = 0) = 0;
		inline static API GetAPI() { return s_API; }
	private:
		static API s_API;
	};
}


