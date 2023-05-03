#include "stdafx.h"
#include "Renderer2D.h"
#include "RendererCommand.h"
#include "VertexArray.h"
#include <memory>
#include <glm/gtc/matrix_transform.hpp>
namespace Engine
{
	struct InstanceData
	{
		
		glm::mat4* Tranform = nullptr;
		glm::vec3* Color = nullptr;
		float* Alpha = nullptr;
		float* TexCoordZ = nullptr;

	};

	struct Renderer2DQuad
	{
		
		static const unsigned int MaxInstance = 2000;
		std::shared_ptr<VertexArray> VAO;
		std::shared_ptr<VertexBuffer> QuadVBO;
		std::shared_ptr<VertexBuffer> TranformVBO;
		std::shared_ptr<VertexBuffer> ColorVBO;
		std::shared_ptr<VertexBuffer> AlphaVBO;
		std::shared_ptr<VertexBuffer> TexCoordZVBO;
		std::shared_ptr<Shader> Shader;
		std::shared_ptr<Texture2DArray> WhiteTexture;

		unsigned int instanceCount = 0;
		InstanceData instanceData;

		Renderer2D::Statistics Stats;
	};


	static Renderer2DQuad s_Data;

	void Renderer2D::Init()
	{

		//ʵ����׼��

		

		//��ɫ������
		s_Data.Shader = Shader::Create("assets/shaders/Texture.glsl");

		s_Data.Shader->SetInteger("u_Texture0", 0, true);
		//VAO
		s_Data.VAO = Engine::VertexArray::Create();
		
		
		//QuadVBO
		float quadVertices[] =
		{
			-0.5, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5,  0.5f, 0.0f, 0.0f, 1.0f
		};
		s_Data.QuadVBO = VertexBuffer::Create(quadVertices,sizeof(quadVertices));
		{
			Engine::BufferLayout layout = {
				{ 0, Engine::ShaderDataType::Float3 },
				{ 1, Engine::ShaderDataType::Float2 }
			};
			s_Data.QuadVBO->SetLayout(layout);
		}
		s_Data.VAO->AddVertexBuffer(s_Data.QuadVBO);

		//TranformVBO
		s_Data.TranformVBO = VertexBuffer::Create(s_Data.MaxInstance * sizeof(glm::mat4));
		{
			Engine::BufferLayout layout = {
				{ 2, Engine::ShaderDataType::Float4, 1 },
				{ 3, Engine::ShaderDataType::Float4, 1 },
				{ 4, Engine::ShaderDataType::Float4, 1 },
				{ 5, Engine::ShaderDataType::Float4, 1 }
			};
			s_Data.TranformVBO->SetLayout(layout);
		}
		s_Data.VAO->AddVertexBuffer(s_Data.TranformVBO);
		s_Data.instanceData.Tranform = new glm::mat4[s_Data.MaxInstance];

		//ColorVBO
		s_Data.ColorVBO = VertexBuffer::Create(s_Data.MaxInstance * sizeof(glm::vec3));
		{
			Engine::BufferLayout layout = {
				{ 6, Engine::ShaderDataType::Float3, 1 }
			};
			s_Data.ColorVBO->SetLayout(layout);
		}
		s_Data.VAO->AddVertexBuffer(s_Data.ColorVBO);
		s_Data.instanceData.Color = new glm::vec3[s_Data.MaxInstance];

		//AlphaVBO
		s_Data.AlphaVBO = VertexBuffer::Create(s_Data.MaxInstance * sizeof(float));
		{
			Engine::BufferLayout layout = {
				{ 7, Engine::ShaderDataType::Float, 1 }
			};
			s_Data.AlphaVBO->SetLayout(layout);
		}
		s_Data.VAO->AddVertexBuffer(s_Data.AlphaVBO);
		s_Data.instanceData.Alpha = new float[s_Data.MaxInstance];
		
		//TexCoordZVBO
		s_Data.TexCoordZVBO = VertexBuffer::Create(s_Data.MaxInstance * sizeof(float));
		{
			Engine::BufferLayout layout = {
				{ 8, Engine::ShaderDataType::Float, 1 }
			};
			s_Data.TexCoordZVBO->SetLayout(layout);
		}
		s_Data.VAO->AddVertexBuffer(s_Data.TexCoordZVBO);
		s_Data.instanceData.TexCoordZ = new float[s_Data.MaxInstance];
		//EBO
		unsigned int indices[] = { 0,1,2,2,3,0 };

		std::shared_ptr<ElementBuffer> m_EBO = ElementBuffer::Create(indices, sizeof(indices) / sizeof(unsigned int));
		s_Data.VAO->SetElementBuffer(m_EBO);
	
		

		//���ɰ�ɫ����
		s_Data.WhiteTexture = Texture2DArray::Create();
	


	}
	void Renderer2D::Shutdown()
	{
	}
	void Renderer2D::BeginScene(const std::shared_ptr<Camera>& camera, std::shared_ptr<Texture2DArray> texture, const std::shared_ptr<Shader> shader)
	{

		ENGINE_CORE_ASSERT(camera, "Renderer needs a camera!")
		
		if (shader == nullptr)
		{
			s_Data.Shader->Use();
			s_Data.Shader->SetMatrix4("u_ViewProjection", camera->GetViewProjectionMatrix());
		}
		else
		{
			shader->Use();
			shader->SetMatrix4("u_ViewProjection", camera->GetViewProjectionMatrix());
		}

		if (texture == nullptr)
		{
			s_Data.WhiteTexture->Bind(0);
		}
		else
		{
			texture->Bind();
		}
		s_Data.instanceCount = 0;
	}
	void Renderer2D::EndScene()
	{
		s_Data.TranformVBO->SetData(s_Data.instanceData.Tranform, s_Data.instanceCount * sizeof(glm::mat4));
		s_Data.ColorVBO->SetData(s_Data.instanceData.Color, s_Data.instanceCount * sizeof(glm::vec3));
		s_Data.AlphaVBO->SetData(s_Data.instanceData.Alpha, s_Data.instanceCount * sizeof(float));
		s_Data.TexCoordZVBO->SetData(s_Data.instanceData.TexCoordZ, s_Data.instanceCount * sizeof(float));
		Flush();
	}
	void Renderer2D::Flush()
	{
		RendererCommand::DrawInstanced(s_Data.VAO, s_Data.instanceCount);
		s_Data.Stats.DrawCalls++;
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color, float texCoordZ)
	{
		DrawQuad(glm::vec3(position.x, position.y, 0.0f), size, rotation, color, texCoordZ);
		
	}
	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color, float texCoordZ)
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
			glm::rotate(glm::mat4(1.0f), rotation, glm::vec3(0.0f, 0.0f, 1.0f)) *
			glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1.0f));
	
		DrawQuad(transform, color, texCoordZ);

	}

	void Renderer2D::DrawQuad(const glm::mat4& transform, const glm::vec4& color, float texCoordZ)
	{
		if (s_Data.instanceCount == s_Data.MaxInstance)
		{
			StartNewBatch();
		}

		//����ʵ��������
		s_Data.instanceData.Tranform[s_Data.instanceCount] = transform;

		s_Data.instanceData.Color[s_Data.instanceCount] = glm::vec3(color.r, color.g, color.b);
		s_Data.instanceData.Alpha[s_Data.instanceCount] = color.a;
		s_Data.instanceData.TexCoordZ[s_Data.instanceCount] = texCoordZ;

		s_Data.instanceCount++;

		s_Data.Stats.QuadCount++;
	}
	

	Renderer2D::Statistics Renderer2D::GetStats()
	{
		return s_Data.Stats;
	}


	void Renderer2D::ResetStats()
	{
		memset(&s_Data.Stats, 0, sizeof(Statistics));
	}



	//�����������ݳ�������ʱ���ύ����
	void Renderer2D::StartNewBatch()
	{
		EndScene();

		s_Data.instanceCount = 0;
	}


	
	
}