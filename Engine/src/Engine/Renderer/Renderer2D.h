#pragma once
#include "Camera.h"
#include "Texture.h"
#include "Shader.h"
namespace Engine
{
	
	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();
		static void BeginScene(const OrthographicCamera& camera, const std::shared_ptr<Texture2DArray> teture = nullptr, const std::shared_ptr<Shader> shader = nullptr);
		static void EndScene();
		static void Flush();

		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color = glm::vec4(1.0f), float texCoordZ = 0);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color = glm::vec4(1.0f), float texCoordZ = 0);
		
		struct Statistics
		{
			unsigned int DrawCalls = 0;
			unsigned int QuadCount = 0;

			unsigned int GetTotalVertexCount() { return QuadCount * 4; }
			unsigned int GetTotalIndexCount() { return QuadCount * 6; }
		};

		static Statistics GetStats();
		static void ResetStats();
	private:
		static void StartNewBatch();
	
	};

}

