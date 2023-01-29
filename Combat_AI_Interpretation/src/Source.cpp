#include "Engine.h"
#include "imgui.h"
#include <memory>
class TestLayer : public Engine::Layer
{
public:
	TestLayer()
		:Layer("Test"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
	{
		//¶¥µãÔØÈë

		float vertices[4 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
			 0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f
		};
		unsigned int indices[6] = { 0, 1, 2, 2, 3, 0 };
		m_VAO.reset(Engine::VertexArray::Create());
		m_VBO.reset(Engine::VertexBuffer::Create(vertices, sizeof(vertices)));
		m_EBO.reset(Engine::ElementBuffer::Create(indices, sizeof(indices) / sizeof(unsigned)));


		{
			Engine::BufferLayout layout = {
				{ Engine::ShaderDataType::Float3, "a_Position" },
				{ Engine::ShaderDataType::Float4, "a_Color" }
			};
			m_VBO->SetLayout(layout);
		}
		m_VAO->AddVertexBuffer(m_VBO);
		m_VAO->SetElementBuffer(m_EBO);

		std::string vertexSrc = R"(
			#version 330 core
			layout (location = 0) in vec3 a_Position;
			layout (location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			
			out vec4 Color;
			
			void main()
			{
				Color = a_Color;
			    gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}

		)";
		std::string fragmentSrc = R"(
			#version 330 core
			in vec4 Color;
			out vec4 color;

			void main()
			{
			    color = Color;

			}

		)";

		m_Shader.reset(new Engine::Shader(vertexSrc, fragmentSrc));

		m_Camera.SetRotation(45.0f);
	
	}
	void OnUpdate() override
	{
		//glViewport(0, 0, m_Window->GetWidth(), m_Window->GetHeight());
		Engine::RendererCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1));
		Engine::RendererCommand::Clear();

		Engine::Renderer::BeginScene(m_Camera);
		Engine::Renderer::Submit(m_VAO, m_Shader);
		Engine::Renderer::EndScene();

		if (Engine::Input::IsKeyPoressed(ENGINE_KEY_TAB))
			ENGINE_TRACE("Tab key is poressed!");

	}
	void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();
	}
	void OnEvent(Engine::Event& event) override
	{
		//ENGINE_TRACE("{0}", event.ToString());
	}
private:

	std::shared_ptr<Engine::Shader> m_Shader;
	std::shared_ptr<Engine::VertexArray> m_VAO;
	std::shared_ptr<Engine::VertexBuffer> m_VBO;
	std::shared_ptr<Engine::ElementBuffer> m_EBO;

	Engine::OrthographicCamera m_Camera;
};

class Game : public Engine::Application
{
public:
	Game()
	{
		AppPushLayer(new TestLayer());
	}

	~Game()
	{
	}

};

Engine::Application* Engine::CreateApp()
{
	return new Game();
}