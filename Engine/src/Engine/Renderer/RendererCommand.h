#pragma once
#include "RendererAPI.h"
namespace Engine
{
	class RendererCommand
	{
	public:
		inline static void Init()
		{
			s_RendererAPI->Init();
		}
		inline static void SetViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height)
		{
			s_RendererAPI->SetViewport(x, y, width, height);
		}

		inline static void SetClearColor(const glm::vec4 color)
		{
			s_RendererAPI->SetClearColor(color);
		}
		inline static void Clear()
		{
			s_RendererAPI->SetStencilMask(0xFF);
			s_RendererAPI->Clear();
			s_RendererAPI->SetStencilMask(0x00);
		}

		inline static void ClearColorBuffer()
		{
			s_RendererAPI->ClearColorBuffer();
		}
		inline static void	ClearDepthBuffer()
		{
			s_RendererAPI->ClearDepthBuffer();
		}
		inline static void	ClearStencilBuffer()
		{
			s_RendererAPI->ClearStencilBuffer();
		}
		inline static void EnableDepthTest()
		{
			s_RendererAPI->EnableDepthTest();
		}
		inline static void DisableDepthTest()
		{
			s_RendererAPI->DisableDepthTest();
		}
		inline static void SetStencilMask(int value)
		{
			s_RendererAPI->SetStencilMask(value);
		}
		inline static void SetStencilFunc(StencilFuncMode func, int ref, unsigned int mask)
		{
			s_RendererAPI->SetStencilFunc(func, ref, mask);
		}
		inline static void Draw(const std::shared_ptr<VertexArray>& vertexArray)
		{
			vertexArray->Bind();
			s_RendererAPI->Draw(vertexArray);
		}
		inline static void DrawInstanced(const std::shared_ptr<VertexArray>& vertexArray, unsigned int count)
		{
			vertexArray->Bind();
			s_RendererAPI->DrawInstanced(vertexArray, count);
		}
	private:
		static RendererAPI* Creat();
		static RendererAPI* s_RendererAPI;
	};
}