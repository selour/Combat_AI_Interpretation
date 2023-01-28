#pragma once
#include "RendererAPI.h"
namespace Engine
{
	class RendererCommand
	{
	public:
		inline static void SetClearColor(const glm::vec4 color)
		{
			s_RendererAPI->SetClearColor(color);
		}
		inline static void Clear()
		{
			s_RendererAPI->Clear();
		}

		inline static void Draw(const std::shared_ptr<VertexArray>& vertexArray)
		{
			vertexArray->Bind();
			s_RendererAPI->Draw(vertexArray);
		}
	private:
		static RendererAPI* s_RendererAPI;
	};
}