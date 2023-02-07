#include "stdafx.h"
#include "Renderer2D.h"
#include "RendererCommand.h"
#include "VertexArray.h"
#include "Shader.h"
#include <memory>
#include <glm/gtc/matrix_transform.hpp>
namespace Engine
{
	struct QuadVertex
	{
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoord;
		float TexIndex;
	};

	struct Renderer2DQuad
	{
		static const unsigned int MaxQuads = 2000;
		static const unsigned int MaxVertices = MaxQuads * 4;
		static const unsigned int MaxIndices = MaxQuads * 6;
		static const unsigned int MaxTextureSlots = 16;

		std::shared_ptr<VertexArray> VAO;
		std::shared_ptr<VertexBuffer> VBO;
		std::shared_ptr<Shader> Shader;
		std::shared_ptr<Texture2D> WhiteTexture;

		unsigned int QuadIndexCount = 0;
		QuadVertex* QuadVertexBufferBase = nullptr;
		QuadVertex* QuadVertexBufferPtr = nullptr;

		std::array<std::shared_ptr<Texture2D>, MaxTextureSlots> TextureSolts;
		unsigned int TextureSoltIndex = 1;

		glm::vec4 QuadVertexPositions[4];

		Renderer2D::Statistics Stats;
	};


	static Renderer2DQuad s_Data;

	void Renderer2D::Init()
	{

		//批处理准备

		s_Data.QuadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
		s_Data.QuadVertexPositions[1] = { 0.5f, -0.5f, 0.0f, 1.0f };
		s_Data.QuadVertexPositions[2] = { 0.5f,  0.5f, 0.0f, 1.0f };
		s_Data.QuadVertexPositions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };
		
		s_Data.VAO = Engine::VertexArray::Create();

		//VBO
		s_Data.VBO = VertexBuffer::Create(s_Data.MaxVertices * sizeof(QuadVertex));
				{
			Engine::BufferLayout layout = {
				{ Engine::ShaderDataType::Float3, "a_Position" },
				{ Engine::ShaderDataType::Float4, "a_Color" },
				{ Engine::ShaderDataType::Float2, "a_TexCoord" },
				{ Engine::ShaderDataType::Float , "a_TexIndex" }
			};
			s_Data.VBO->SetLayout(layout);
		}
		s_Data.VAO->AddVertexBuffer(s_Data.VBO);
		s_Data.QuadVertexBufferBase = new QuadVertex[s_Data.MaxVertices];

		
		//EBO
		unsigned int* indices = new unsigned int[s_Data.MaxIndices];
		unsigned int offset = 0;
		for (unsigned int i = 0; i < s_Data.MaxIndices; i += 6)
		{
			indices[i + 0] = offset + 0;
			indices[i + 1] = offset + 1;
			indices[i + 2] = offset + 2;

			indices[i + 3] = offset + 2;
			indices[i + 4] = offset + 3;
			indices[i + 5] = offset + 0;

			offset += 4;
		}

		std::shared_ptr<ElementBuffer> m_EBO = ElementBuffer::Create(indices, s_Data.MaxIndices);
		s_Data.VAO->SetElementBuffer(m_EBO);
		delete[] indices;

		//着色器载入
		int samplers[s_Data.MaxTextureSlots];
		for (int i = 0; i < s_Data.MaxTextureSlots; i++)
		{
			samplers[i] = i;
		}
		s_Data.Shader = Shader::Create("assets/shaders/Texture.glsl");
		s_Data.Shader->SetIntegerArray("u_Textures", samplers, s_Data.MaxTextureSlots, true);

		

		//生成白色纹理
		s_Data.WhiteTexture = Texture2D::Create(1, 1);
		unsigned int WhiteData = 0xffffffff;
		s_Data.WhiteTexture->SetData(&WhiteData, sizeof(unsigned int));

		s_Data.TextureSolts[0] = s_Data.WhiteTexture;
	


	}
	void Renderer2D::Shutdown()
	{
	}
	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		s_Data.Shader->SetMatrix4("u_ViewProjection", camera.GetViewProjectionMatrix(), true);
		s_Data.QuadIndexCount = 0;
		s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;
		s_Data.TextureSoltIndex = 1;
	}
	void Renderer2D::EndScene()
	{
		unsigned int dataSize = (unsigned char*)s_Data.QuadVertexBufferPtr - (unsigned char*)s_Data.QuadVertexBufferBase;
		s_Data.VBO->SetData(s_Data.QuadVertexBufferBase, dataSize);
		Flush();
	}
	void Renderer2D::Flush()
	{

		for (uint32_t i = 0; i < s_Data.TextureSoltIndex; i++)
		{
			s_Data.TextureSolts[i]->Bind(i);
		}

		RendererCommand::Draw(s_Data.VAO, s_Data.QuadIndexCount);
		s_Data.Stats.DrawCalls++;
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad(glm::vec3(position.x, position.y, 0.0f), size, color);
		
	}
	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		if (s_Data.QuadIndexCount >= Renderer2DQuad::MaxIndices)
		{
			StartNewBatch();
		}
		const glm::vec2 textureCoords[] = {
			{ 0.0f, 0.0f },
			{ 1.0f, 0.0f },
			{ 1.0f, 1.0f },
			{ 0.0f, 1.0f },
		};
		float textureIndex = 0.0f;

		//载入顶点数据
		LoadVectex(position, size, color, textureCoords, textureIndex);

		s_Data.Stats.QuadCount++;


	}
	
	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const std::shared_ptr<Texture2D> texture, const glm::vec4& color)
	{
		DrawQuad(glm::vec3(position.x, position.y, 0.0f), size, texture, color);
	}
	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const std::shared_ptr<Texture2D> texture, const glm::vec4& color)
	{
		
		if (s_Data.QuadIndexCount >= Renderer2DQuad::MaxIndices)
		{
			StartNewBatch();
		}
		const glm::vec2 textureCoords[] = {
			{ 0.0f, 0.0f },
			{ 1.0f, 0.0f },
			{ 1.0f, 1.0f },
			{ 0.0f, 1.0f },
		};
		float textureIndex = 0.0f;
		for (unsigned int i = 0; i < s_Data.TextureSoltIndex; i++)
		{
			if (*s_Data.TextureSolts[i].get() == *texture.get())
			{
				textureIndex = (float)i;
				break;
			}
		}
		if (textureIndex == 0.0f)
		{
			textureIndex = (float)s_Data.TextureSoltIndex;
			s_Data.TextureSolts[s_Data.TextureSoltIndex] = texture;
			s_Data.TextureSoltIndex++;

		}
		//载入顶点数据
		LoadVectex(position, size, color, textureCoords, textureIndex);

		s_Data.Stats.QuadCount++;
	}


	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const std::shared_ptr<SubTexture2D> subTexture, const glm::vec4& color)
	{
		DrawQuad(glm::vec3(position.x, position.y, 0.0f), size, subTexture, color);
	}
	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const std::shared_ptr<SubTexture2D> subTexture, const glm::vec4& color)
	{
		
		if (s_Data.QuadIndexCount >= Renderer2DQuad::MaxIndices)
		{
			StartNewBatch();
		}

		const glm::vec2* textureCoords = subTexture->GetTexCoord();
		const std::shared_ptr<Texture2D> texture = subTexture->GetTexture();
		float textureIndex = 0.0f;
		for (unsigned int i = 0; i < s_Data.TextureSoltIndex; i++)
		{
			if (*s_Data.TextureSolts[i].get() == *texture.get())
			{
				textureIndex = (float)i;
				break;
			}
		}
		if (textureIndex == 0.0f)
		{
			textureIndex = (float)s_Data.TextureSoltIndex;
			s_Data.TextureSolts[s_Data.TextureSoltIndex] = texture;
			s_Data.TextureSoltIndex++;

		}
		LoadVectex(position, size, color, textureCoords, textureIndex);

		s_Data.Stats.QuadCount++;
	}










	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color, const glm::vec3& rotationAxis)
	{
		DrawRotatedQuad(glm::vec3(position.x, position.y, 0.0f), size, rotation, color, rotationAxis);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color, const glm::vec3& rotationAxis)
	{
		if (s_Data.QuadIndexCount >= Renderer2DQuad::MaxIndices)
		{
			StartNewBatch();
		}
		const glm::vec2 textureCoords[] = {
			{ 0.0f, 0.0f },
			{ 1.0f, 0.0f },
			{ 1.0f, 1.0f },
			{ 0.0f, 1.0f },
		};
		float textureIndex = 0.0f;
		glm::mat4 tranform = glm::translate(glm::mat4(1.0f), position) *
			glm::rotate(glm::mat4(1.0f), rotation, rotationAxis) *
			glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1.0f));

		LoadRotatedVectex(tranform, color, textureCoords, textureIndex);
		
		s_Data.Stats.QuadCount++;
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const std::shared_ptr<Texture2D> texture, const glm::vec4& color, const glm::vec3& rotationAxis)
	{
		DrawRotatedQuad(glm::vec3(position.x, position.y, 0.0f), size, rotation, texture, color, rotationAxis);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const std::shared_ptr<Texture2D> texture, const glm::vec4& color, const glm::vec3& rotationAxis)
	{
		if (s_Data.QuadIndexCount >= Renderer2DQuad::MaxIndices)
		{
			StartNewBatch();
		}	
		const glm::vec2 textureCoords[] = {
			{ 0.0f, 0.0f },
			{ 1.0f, 0.0f },
			{ 1.0f, 1.0f },
			{ 0.0f, 1.0f },
		};
		float textureIndex = 0.0f;
		for (unsigned int i = 0; i < s_Data.TextureSoltIndex; i++)
		{
			if (*s_Data.TextureSolts[i].get() == *texture.get())
			{
				textureIndex = (float)i;
				break;
			}
		}
		if (textureIndex == 0.0f)
		{
			textureIndex = (float)s_Data.TextureSoltIndex;
			s_Data.TextureSolts[s_Data.TextureSoltIndex] = texture;
			s_Data.TextureSoltIndex++;

		}
		glm::mat4 tranform = glm::translate(glm::mat4(1.0f), position) *
			glm::rotate(glm::mat4(1.0f), rotation, rotationAxis) *
			glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1.0f));

		LoadRotatedVectex(tranform, color, textureCoords, textureIndex);


		s_Data.Stats.QuadCount++;
	}
	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const std::shared_ptr<SubTexture2D> subTexture, const glm::vec4& color, const glm::vec3& rotationAxis)
	{
		DrawRotatedQuad(glm::vec3(position.x, position.y, 0.0f), size, rotation, subTexture, color, rotationAxis);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const std::shared_ptr<SubTexture2D> subTexture, const glm::vec4& color, const glm::vec3& rotationAxis)
	{
		if (s_Data.QuadIndexCount >= Renderer2DQuad::MaxIndices)
		{
			StartNewBatch();
		}
		const glm::vec2* textureCoords = subTexture->GetTexCoord();
		const std::shared_ptr<Texture2D> texture = subTexture->GetTexture();
		float textureIndex = 0.0f;
		for (unsigned int i = 0; i < s_Data.TextureSoltIndex; i++)
		{
			if (*s_Data.TextureSolts[i].get() == *texture.get())
			{
				textureIndex = (float)i;
				break;
			}
		}
		if (textureIndex == 0.0f)
		{
			textureIndex = (float)s_Data.TextureSoltIndex;
			s_Data.TextureSolts[s_Data.TextureSoltIndex] = texture;
			s_Data.TextureSoltIndex++;

		}
		glm::mat4 tranform = glm::translate(glm::mat4(1.0f), position) *
			glm::rotate(glm::mat4(1.0f), rotation, rotationAxis) *
			glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1.0f));

		LoadRotatedVectex(tranform, color, textureCoords, textureIndex);


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



	//当批处理数据超出上限时，提交数据
	void Renderer2D::StartNewBatch()
	{
		EndScene();

		s_Data.QuadIndexCount = 0;
		s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;
		s_Data.TextureSoltIndex = 1;
	}

	void Renderer2D::LoadVectex(const glm::vec3& position, const glm::vec2 size, const glm::vec4& color, const glm::vec2* textureCoords, float textureIndex)
	{
		//载入顶点数据
		s_Data.QuadVertexBufferPtr->Position = glm::vec3(position.x - size.x / 2, position.y - size.y / 2, position.z);;
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = textureCoords[0];
		s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
		++s_Data.QuadVertexBufferPtr;

		s_Data.QuadVertexBufferPtr->Position = glm::vec3(position.x + size.x / 2, position.y - size.y / 2, position.z);
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = textureCoords[1];
		s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
		++s_Data.QuadVertexBufferPtr;

		s_Data.QuadVertexBufferPtr->Position = glm::vec3(position.x + size.x / 2, position.y + size.y / 2, position.z);
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = textureCoords[2];
		s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
		++s_Data.QuadVertexBufferPtr;

		s_Data.QuadVertexBufferPtr->Position = glm::vec3(position.x - size.x / 2, position.y + size.y / 2, position.z);
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = textureCoords[3];
		s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
		++s_Data.QuadVertexBufferPtr;
		s_Data.QuadIndexCount += 6;
	}

	void Renderer2D::LoadRotatedVectex(const glm::mat4 tranform, const glm::vec4& color, const glm::vec2* textureCoords, float textureIndex)
	{
		//载入顶点数据
		s_Data.QuadVertexBufferPtr->Position = tranform * s_Data.QuadVertexPositions[0];
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = textureCoords[0];
		s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
		++s_Data.QuadVertexBufferPtr;

		s_Data.QuadVertexBufferPtr->Position = tranform * s_Data.QuadVertexPositions[1];
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = textureCoords[1];
		s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
		++s_Data.QuadVertexBufferPtr;

		s_Data.QuadVertexBufferPtr->Position = tranform * s_Data.QuadVertexPositions[2];
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = textureCoords[2];
		s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
		++s_Data.QuadVertexBufferPtr;

		s_Data.QuadVertexBufferPtr->Position = tranform * s_Data.QuadVertexPositions[3];
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = textureCoords[3];
		s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
		++s_Data.QuadVertexBufferPtr;
		s_Data.QuadIndexCount += 6;
	}





	
}