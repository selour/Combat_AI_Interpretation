#include "stdafx.h"
#include "Renderer2D.h"
#include "RendererCommand.h"
#include "VertexArray.h"
#include "Shader.h"
#include <memory>
#include <glm/gtc/matrix_transform.hpp>
namespace Engine
{
	struct Renderer2DQuad
	{
		std::shared_ptr<VertexArray> VAO;
		std::shared_ptr<Shader> Shader;
		std::shared_ptr<Texture2D> WhiteTexture;
	};
	static Renderer2DQuad* s_Quad;
	void Renderer2D::Init()
	{
		s_Quad = new Renderer2DQuad();

		//顶点载入

		float vertices[4 * 5] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};
		unsigned int indices[6] = { 0, 1, 2, 2, 3, 0 };
		s_Quad->VAO = Engine::VertexArray::Create();
		std::shared_ptr<VertexBuffer> m_VBO = Engine::VertexBuffer::Create(vertices, sizeof(vertices));
		std::shared_ptr<ElementBuffer> m_EBO = Engine::ElementBuffer::Create(indices, sizeof(indices) / sizeof(unsigned));


		{
			Engine::BufferLayout layout = {
				{ Engine::ShaderDataType::Float3, "a_Position" },
				{ Engine::ShaderDataType::Float2, "a_TexCoord" }
			};
			m_VBO->SetLayout(layout);
		}
		s_Quad->VAO->AddVertexBuffer(m_VBO);
		s_Quad->VAO->SetElementBuffer(m_EBO);

		//着色器载入
		
		s_Quad->Shader = Shader::Create("assets/shaders/Texture.glsl");
		s_Quad->Shader->SetInteger("u_Texture", 0);

		//生成白色纹理
		s_Quad->WhiteTexture = Texture2D::Create(1, 1);
		unsigned int WhiteData = 0xffffffff;
		s_Quad->WhiteTexture->SetData(&WhiteData, sizeof(unsigned int));
	}
	void Renderer2D::Shutdown()
	{
		delete s_Quad;
	}
	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		s_Quad->Shader->SetMatrix4("u_ViewProjection", camera.GetViewProjectionMatrix(), true);
	}
	void Renderer2D::EndScene()
	{
	}
	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad(glm::vec3(position.x, position.y, 0.0f), size, color);
		
	}
	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		glm::mat4 tranform = glm::translate(glm::mat4(1.0f), position) *
			glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1.0f));

		s_Quad->Shader->Use();
		s_Quad->Shader->SetVector4f("u_Color", color);
		s_Quad->Shader->SetMatrix4("u_Model", tranform);
		s_Quad->WhiteTexture->Bind();
		RendererCommand::Draw(s_Quad->VAO);
	}
	
	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const std::shared_ptr<Texture2D> texture, const glm::vec4& color)
	{
		DrawQuad(glm::vec3(position.x, position.y, 0.0f), size, texture, color);
	}
	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const std::shared_ptr<Texture2D> texture, const glm::vec4& color)
	{
		glm::mat4 tranform = glm::translate(glm::mat4(1.0f), position) *
			glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1.0f));

		s_Quad->Shader->Use();
		s_Quad->Shader->SetVector4f("u_Color", color);
		s_Quad->Shader->SetMatrix4("u_Model", tranform);
		texture->Bind();
		RendererCommand::Draw(s_Quad->VAO);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		DrawRotatedQuad(glm::vec3(position.x, position.y, 0.0f), size, rotation, color);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		glm::mat4 tranform = glm::translate(glm::mat4(1.0f), position) *
			glm::rotate(glm::mat4(1.0f), rotation, glm::vec3(0.0f, 0.0f, 1.0f)) *
			glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1.0f));

		s_Quad->Shader->Use();
		s_Quad->Shader->SetVector4f("u_Color", color);
		s_Quad->Shader->SetMatrix4("u_Model", tranform);
		s_Quad->WhiteTexture->Bind();
		RendererCommand::Draw(s_Quad->VAO);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const std::shared_ptr<Texture2D> texture, const glm::vec4& color)
	{
		DrawRotatedQuad(glm::vec3(position.x, position.y, 0.0f), size, rotation, texture, color);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const std::shared_ptr<Texture2D> texture, const glm::vec4& color)
	{
		glm::mat4 tranform = glm::translate(glm::mat4(1.0f), position) *
			glm::rotate(glm::mat4(1.0f), rotation, glm::vec3(0.0f, 0.0f, 1.0f)) *
		glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1.0f));

		s_Quad->Shader->Use();
		s_Quad->Shader->SetVector4f("u_Color", color);
		s_Quad->Shader->SetMatrix4("u_Model", tranform);
		texture->Bind();
		RendererCommand::Draw(s_Quad->VAO);
	}
	
}