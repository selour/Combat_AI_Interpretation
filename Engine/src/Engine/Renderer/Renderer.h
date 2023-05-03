#pragma once
#include "RendererCommand.h"
#include "Camera.h"
#include "Shader.h"
namespace Engine
{
	
	class Renderer
	{
	public:
		static void Init();

		static void OnWindowResize(unsigned int width, unsigned int height);
		static void BeginScene(const std::shared_ptr<Camera>& camera);
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, glm::mat4 model);


		inline static RendererAPI::API GetRendererAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};
		static SceneData* s_SceneData;
	};


}
