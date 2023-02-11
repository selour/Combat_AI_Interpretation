#include "stdafx.h"
#include "RendererPostProcessing.h"
#include "RendererCommand.h"
#include "VertexArray.h"

namespace Engine
{
	struct ScreenQuad
	{
		std::shared_ptr<VertexArray> VAO;
		std::shared_ptr<VertexBuffer> QuadVBO;
		std::shared_ptr<Shader> Shader;
	};
	static ScreenQuad s_Data;
	void RendererPostProcessing::Init()
	{
		//×ÅÉ«Æ÷ÔØÈë
		s_Data.Shader = Shader::Create("assets/shaders/PostProcessing.glsl");
		s_Data.Shader->SetInteger("u_Texture0", 0, true);
		//VAO
		s_Data.VAO = Engine::VertexArray::Create();
		//QuadVBO
		float quadVertices[] =
		{
			-1.0, -1.0f, 0.0f, 0.0f,
			 1.0, -1.0f, 1.0f, 0.0f,
			 1.0,  1.0f, 1.0f, 1.0f,
			-1.0,  1.0f, 0.0f, 1.0f
		};
		s_Data.QuadVBO = VertexBuffer::Create(quadVertices, sizeof(quadVertices));
		{
			Engine::BufferLayout layout = {
				{ 0, Engine::ShaderDataType::Float2 },
				{ 1, Engine::ShaderDataType::Float2 }
			};
			s_Data.QuadVBO->SetLayout(layout);
		}
		s_Data.VAO->AddVertexBuffer(s_Data.QuadVBO);
		//EBO
		unsigned int indices[] = { 0,1,2,2,3,0 };

		std::shared_ptr<ElementBuffer> m_EBO = ElementBuffer::Create(indices, sizeof(indices) / sizeof(unsigned int));
		s_Data.VAO->SetElementBuffer(m_EBO);

	}
	void RendererPostProcessing::Shutdown()
	{
	}
	void RendererPostProcessing::Draw(const std::shared_ptr<FrameBuffer> frameBuffer, const std::shared_ptr<Shader> shader)
	{
		frameBuffer->BindColorAttachment(0);
		if (shader == nullptr)
		{
			s_Data.Shader->Use();
		}
		else
		{
			shader->Use();
		}
		RendererCommand::Draw(s_Data.VAO);
	}
}